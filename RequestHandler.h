#pragma once

// Include all Regex classes from RequestParser.h
#include "RequestParser.h"

// Standard Templete Library.
// Note: Contains key-value pairs with unique keys.
#include <map>
// STL vector - Used to store Messageboard posts - size can change during compilation.
#include <vector>
// Used for shared mutex - Threads. (shared_lock)
#include <shared_mutex>
// Used for locking - Threads. (unique_lock)
#include <mutex>

class RequestHandler
{
public:

	// Default Constructor.
	RequestHandler(std::string request);

	// Destructor.
	~RequestHandler();

	// Check the type of request & call correct method.
	void checkRequest(std::string request);

	// Handlers for Server requests recieved from the client.
	std::string postMessageHandler(std::string request);
	std::string listMessageHandler(std::string request);
	std::string countMessageHandler(std::string request);
	std::string readMessageHandler(std::string request);
	std::string terminateRequestHandler(std::string request);

private:

	/*
	// NOTE: STL Map seems preferable over a Hash-Table for implementation.
	// NOTE: Map would run faster - Hash-table would be better for Multithreading safety.
	// NOTE: Map is faster, therefore the optimal choice.
	// Map will hold:
	// std::string - PostID name.
	// std::vector<std::string> - Vector of strings to contain the messages - Post Message.
	*/
	std::map <std::string, std::vector<std::string>> messageBoard;

	// Shared Mutex (mutual exclusion).
	std::shared_mutex sharedMutex;

	// Regex Parsers Instantiated.
	PostRequest postParser;
	ReadRequest readParser;
	CountRequest countParser;
	ListRequest listParser;
	ExitRequest exitParser;
};