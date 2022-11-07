#pragma once

#include "TCPClient.h"
#include "RequestParser.h"

#include <string>
#include <chrono>
#include <future>
#include <vector>

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
	std::string generateReadRequest();

	// Generate a random message.
	std::string generateRandomMessage();
	// Generate a random request.
	int generateRandomRequest();
	// Create a new client.
	void createNewTest();

	// Return output results.
	void outputResults();

private:

	const int SERVER_DEFAULT_PORT = 12345;

	// Number of POST and READ threads.
	int postThreads;
	int readThreads;
		
	// Runtime in seconds.
	int runTime;

	// Incremental counter.
	int incrementalCounter = 0;

	// Recording data.
	int totalPostRequests;
	int averageRequestsPerPosterThread;
	int totalReaderRequests;
	int averageRequestsPerReaderThread;
	int totalRequests;
	int averageRequestsPerThread;
	int requestsPerThreadPerSecond;

	// Vector of std::future variables using std::asynch using threads. 
	// Instantiate size.
	std::vector<std::future<std::vector<float>>> readData = std::vector<std::future<std::vector<float>>>(readThreads);
	std::vector<std::future<std::vector<float>>> postData = std::vector<std::future<std::vector<float>>>(postThreads);

	std::vector<float> runTest();
};

