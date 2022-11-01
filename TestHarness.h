#pragma once

#include <string>

class TestHarness
{
/*
	Class created as a Test Harness using the TCPClient for use on the TCPServer.
*/
public:

	// Default constructor.
	TestHarness();
	// Overloaded constructor.
	TestHarness(int postThreads, int readThreads, int runTime);

	// Destructor.
	~TestHarness();

	// Methods to generate each type of request.
	std::string generatePostRequest();
	std::string generateListRequest();
	std::string generateCountRequest();
	std::string generateReadRequest();
	std::string generateExitRequest();

	// Generate a random message.
	std::string generateRandomMessage();
	// Generate a random request.
	int generateRandomRequest();

	// Return output results.
	void outputResults();

private:

	// Number of POST and READ threads.
	int postThreads;
	int readThreads;
		
	// Runtime in seconds.
	int runTime;

	// Recording data.
	int totalPostRequests;
	int averageRequestsPerPosterThread;
	int totalReaderRequests;
	int averageRequestsPerReaderThread;
	int totalRequests;
	int averageRequestsPerThread;
	int requestsPerThreadPerSecond;
};

