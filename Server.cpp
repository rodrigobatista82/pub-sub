#include "Server.h"

TopicContent& Server::createTopicContent(const std::string& topic) {
	// try_emplace() will insert a new TopicContent only if "topic" not found
	const auto topic_it = topics.try_emplace(topic);

	return topic_it.first->second;
}

void Server::publish(const std::string& topic, const std::string& message) {
	createTopicContent(topic).publish(message);
}

void Server::subscribe(const std::string& topic, const std::string& subscriber) {
	createTopicContent(topic).subscribe(subscriber);
}

void Server::unsubscribe(const std::string& topic, const std::string& subscriber) {
	const auto topic_it = topics.find(topic);

	if (topic_it == topics.end()) {
		return;
	}

	topic_it->second.unsubscribe(subscriber);
}

bool Server::poll(const std::string& topic, const std::string& subscriber, std::string& message) {
	const auto topic_it = topics.find(topic);

	if (topic_it == topics.end()) {
		return false;
	}

	return topic_it->second.poll(subscriber, message);
}
