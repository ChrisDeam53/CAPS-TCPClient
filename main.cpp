#include <iostream>

#include "TCPClient.h"
#include "TestHarness.h"

#define DEFAULT_PORT 12345

int main(int argc, char **argv)
{
	// Validate the parameters.
	if (argc != 2) {
		printf("usage: %s server-name|IP-address\n", argv[0]);
		return 1;
	}

	TCPClient client(argv[1], DEFAULT_PORT);
	std::string request;

	client.OpenConnection();

	int postThreads, readThreads, runTime;
	std::cout << "Enter the number of POST threads you would like:" << std::endl;
	std::cin >> postThreads;
	std::cout << "Enter the number of READ threads you would like:" << std::endl;
	std::cin >> readThreads;
	std::cout << "Enter the number of seconds you would like to run for:" << std::endl;
	std::cin >> runTime;
	TestHarness testClient(postThreads, readThreads, runTime);

	// Will probably want to remove
	do {
		request = "";
		std::cout << "Enter string to send to server or \"exit\" (without quotes to terminate): ";

		std::cin >> request;

		std::string reply = client.send(request);
	} while (request != "exit" && request != "EXIT");

	client.CloseConnection();

	return 0;
}
