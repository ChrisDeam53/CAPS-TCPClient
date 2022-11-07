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
	std::string testHarnessChoice;
	int postThreads, readThreads, runTime;

	

	client.OpenConnection();

	std::cout << "Would you like to manually OR automatically test?" << std::endl;
	std::cout << "Enter: \"1\" for Manual Testing, \"2\" for Automatic Testing or \"exit\" to exit the program (without quotes to terminate or to test)" << std::endl;
	std::cin >> testHarnessChoice;

	do 
	{
		if (testHarnessChoice == "1")
		{
			do {
				request = "";
				std::cout << "Enter string to send to server or \"exit\" (without quotes to terminate): ";

				std::cin >> request;

				std::string reply = client.send(request);
			} while (request != "exit" && request != "EXIT");

			client.CloseConnection();
			return 0;
		}
		else if (testHarnessChoice == "2")
		{
			std::cout << "Enter the number of POST threads you would like:" << std::endl;
			std::cin >> postThreads;

			std::cout << "Enter the number of READ threads you would like:" << std::endl;
			std::cin >> readThreads;

			std::cout << "Enter the number of seconds you would like to run for:" << std::endl;
			std::cin >> runTime;

			TestHarness testClient(postThreads, readThreads, runTime);

			client.CloseConnection();
			return 0;
		}

	} while (testHarnessChoice != "exit" && testHarnessChoice != "EXIT");

	client.CloseConnection();
	return 0;
}
