#include <deque>
#include <string>
#include <utility>
#include <map>
#include <set>

class TopicContent {
 private:
	// the message of topic and the number of subscribers remaining to deliver it
	typedef std::pair<std::string, int> message_t;

	// message list
	std::deque<message_t> messages;

	// subscribers list
	std::set<std::string> subscribers;

	// subscribers -> messages list
	std::multimap<std::string, message_t&> subscribers_messages;

	void readMessage(message_t& message);

 public:
	TopicContent() = default;

	void publish(const std::string& message);

	void subscribe(const std::string& subscriber);

	void unsubscribe(const std::string& subscriber);

	bool poll(const std::string& subscriber, std::string& message);
};
