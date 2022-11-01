#include "TestHarness.h"

#include <string>
#include <iostream>
#include <random>
#include <cstdlib>
#include <time.h>

TestHarness::TestHarness() : postThreads(0), readThreads(0), runTime(0)
{

}

TestHarness::TestHarness(int postThreads, int readThreads, int runTime) : postThreads(postThreads), readThreads(readThreads), runTime(runTime)
{
	srand(time(NULL));
}

TestHarness::~TestHarness()
{

}

/*
@brief Outputs the results to the console after the tests have been run.
*/
void TestHarness::outputResults()
{
	std::cout << "Total Post Requests: " << totalPostRequests << std::endl;
	std::cout << "Average Requests Per Poster Thread: " << averageRequestsPerPosterThread << std::endl;
	std::cout << "Total Reader Requests: " << totalReaderRequests << std::endl;
	std::cout << "Average Requests Per Reader Thread: " << averageRequestsPerReaderThread << std::endl;
	std::cout << "Total Requests: " << totalRequests << std::endl;
	std::cout << "Average Requests Per Thread" << averageRequestsPerThread << std::endl;
	std::cout << "Requests Per Thread Per Second" << requestsPerThreadPerSecond << std::endl;
}

/*
@brief Generates a random string to send.
*/
std::string TestHarness::generateRandomMessage()
{
	// String containing the alphabet.
	static std::string letters = "abcdefghijklmnopqrstuvwxyz";
	const int lettersSize = 26;
	
	std::string returnArray;

	for (int i = 0; i < 7; i++)
	{
		int randomLetter = letters[rand() % lettersSize];

		// += seemingly the fastest way to concatiante a string.
		returnArray += randomLetter;
	}
	
	return returnArray;
}


int TestHarness::generateRandomRequest()
{

	return 0;
}

std::string TestHarness::generatePostRequest()
{

	return "";
}

std::string TestHarness::generateListRequest()
{

	return "";
}

std::string TestHarness::generateCountRequest()
{

	return "";
}

std::string TestHarness::generateReadRequest()
{

	return "";
}

std::string TestHarness::generateExitRequest()
{

	return "";
}