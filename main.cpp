#include <iostream>
#include <string>
#include "Server.h"

int main() {
	Server server;
	int opt;

	do {
		std::string topic;
		std::string subscriber;
		std::string message;

		std::cout << std::endl <<
			"1 - publish" << std::endl <<
			"2 - subscribe" << std::endl <<
			"3 - unsubscribe" << std::endl <<
			"4 - poll" << std::endl <<
			"0 - exit" << std::endl;

		std::cin >> opt;

		switch (opt) {
		case 1:
			std::cout << std::endl << "--- Publish ---" << std::endl;

			std::cout << "Enter the topic name: ";
			std::getline(std::cin >> std::ws, topic);

			std::cout << "Enter the message: ";
			std::getline(std::cin >> std::ws, message);

			server.publish(topic, message);
			break;
		case 2:
			std::cout << std::endl << "--- Subscribe ---" << std::endl;

			std::cout << "Enter the topic name: ";
			std::getline(std::cin >> std::ws, topic);

			std::cout << "Enter the subscribe name: ";
			std::getline(std::cin >> std::ws, subscriber);

			server.subscribe(topic, subscriber);
			break;
		case 3:
			std::cout << std::endl << "--- Unsubscribe ---" << std::endl;

			std::cout << "Enter the topic name: ";
			std::getline(std::cin >> std::ws, topic);

			std::cout << "Enter the subscribe name: ";
			std::getline(std::cin >> std::ws, subscriber);

			server.unsubscribe(topic, subscriber);
			break;
		case 4:
			std::cout << std::endl << "--- Poll ---" << std::endl;

			std::cout << "Enter the topic name: ";
			std::getline(std::cin >> std::ws, topic);

			std::cout << "Enter the subscribe name: ";
			std::getline(std::cin >> std::ws, subscriber);

			if (server.poll(topic, subscriber, message)) {
				std::cout << "Poll success!" << std::endl;
				std::cout << "Message: " << message;
			} else {
				std::cout << "Poll error!" << std::endl;
			}
			break;
		}
	} while (opt != 0);

	std::cout << "Exiting..." << std::endl;

	return 0;
}
