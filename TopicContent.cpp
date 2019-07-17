#include "TopicContent.h"

void TopicContent::readMessage(message_t& message) {
	message.second--;  // updating the message read count

	if (!message.second) {
		// everyone read this message, so removing the message from topic
		// finding the first message that has zero read count, because only one message have this value at this time

		for (auto it = messages.begin(); it != messages.end(); ++it) {
			if (!it->second) {
				messages.erase(it);
				break;
			}
		}
	}
}

void TopicContent::publish(const std::string& message) {
	const int sub_count = subscribers.size();

	if (!sub_count) {
		return;  // there are no subscribers, so message will be discarded
	}

	// storing the message and the number of subscribers that will see this message
	auto& msg_ref = messages.emplace_back(message, sub_count);

	// storing the message reference for each subscriber
	for (const auto& s : subscribers) {
		subscribers_messages.emplace(s, msg_ref);
	}
}

void TopicContent::subscribe(const std::string& subscriber) {
	// new subscribers will not see old messages
	// so just insert it into the subscribers list
	subscribers.emplace(subscriber);
}

void TopicContent::unsubscribe(const std::string& subscriber) {
	const auto range = subscribers_messages.equal_range(subscriber);

	// updating the read count of messages, before remove the subscriber
	for (auto i = range.first; i != range.second; ++i) {
		readMessage(i->second);
	}

	subscribers_messages.erase(subscriber);  // erasing all messages for the subscriber
	subscribers.erase(subscriber);  // removing the subscriber
}

bool TopicContent::poll(const std::string& subscriber, std::string& message) {
	if (subscribers.find(subscriber) == subscribers.end()) {
		return false;  // subscriber not found
	}

	// using lower_bound() instead of find() because we need to get the
	// oldest message for this subscriber
	const auto sub_it = subscribers_messages.lower_bound(subscriber);

	if (sub_it == subscribers_messages.end() || sub_it->first != subscriber) {
		message = "";  // there is no message for this subscriber
	} else {
		message_t& msg = sub_it->second;

		message = msg.first;
		subscribers_messages.erase(sub_it);  // remove this message for the subscriber
		readMessage(msg);  // mark message as read
	}

	return true;
}
