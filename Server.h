#include <map>
#include <string>
#include "TopicContent.h"

class Server {
 private:
	std::map<std::string, TopicContent> topics;  // topic name / topic content

	TopicContent& createTopicContent(const std::string& topic);

 public:
	 Server() = default;

	void publish(const std::string& topic, const std::string& message);

	void subscribe(const std::string& topic, const std::string& subscriber);

	void unsubscribe(const std::string& topic, const std::string& subscriber);

	bool poll(const std::string& topic, const std::string& subscriber, std::string& message);
};
