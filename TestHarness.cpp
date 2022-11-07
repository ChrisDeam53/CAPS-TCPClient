#include "TestHarness.h"

#include <string>
#include <iostream>
#include <random>
#include <cstdlib>
#include <time.h>
#include <vector>

TestHarness::TestHarness() : postThreads(0), readThreads(0), runTime(0)
{

}

TestHarness::TestHarness(int postThreads, int readThreads, int runTime) : postThreads(postThreads), readThreads(readThreads), runTime(runTime)
{
	// Initialse the time on creation.
	srand(time(NULL));

	// Runs asynchronously and returns a std::future that will hold the result of the function call.
	for (int i = 0; i < readThreads; i++)
	{
		readData[i] = std::async(std::launch::async, &TestHarness::runTest, this);
	}
	for (int i = 0; i < postThreads; i++)
	{
		postData[i] = std::async(std::launch::async, &TestHarness::runTest, this);
	}
}

TestHarness::~TestHarness()
{

}

std::vector<float> TestHarness::runTest()
{
	int numberOfSeconds = 1;
	std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();
	std::vector<float> runTestData;
	// Instantiate a new client. IP & Port.
	TCPClient newClient("127.0.0.1", SERVER_DEFAULT_PORT);

	// New client added, therefore add a new thread.
	runTestData.push_back(1);

	// Connect to the server.
	newClient.OpenConnection();

	return runTestData;
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
	
	std::string returnMessage;

	incrementalCounter++;

	returnMessage = std::to_string(incrementalCounter);
	
	return returnMessage;
}


int TestHarness::generateRandomRequest()
{
	int randomNum = rand() % 1;

	if (randomNum == 0)
	{
		generatePostRequest();
	}
	else
	{
		generateReadRequest();
	}

	return 0;
}

std::string TestHarness::generatePostRequest()
{

	return "";
}

std::string TestHarness::generateReadRequest()
{

	return "";
}

void TestHarness::createNewTest()
{

}