#include "RequestHandler.h"

RequestHandler::RequestHandler(std::string request)
{
	// Instantiate all Request classes from RequestParser.h.
	PostRequest postParser;
	ReadRequest readParser;
	CountRequest countParser;
	ListRequest listParser;
	ExitRequest exitParser;

	checkRequest(request);
}

RequestHandler::~RequestHandler()
{

}

void RequestHandler::checkRequest(std::string request)
{
	if (request.find("EXIT" || "exit") != std::string::npos)
	{
		// Check if the request is not an exit first.
		// Terminates the server.
		terminateRequestHandler(request);
	}
	else if (request.rfind("POST") != std::string::npos)
	{
		// Post a message.
		postMessageHandler(request);
	}
	else if (request.rfind("LIST") != std::string::npos)
	{
		// List all topicIDs.
		listMessageHandler(request);
	}
	else if (request.rfind("COUNT") != std::string::npos)
	{
		// Counts the number of posts on a given topic, identified by topicID.
		countMessageHandler(request);
	}
	else if (request.rfind("READ") != std::string::npos)
	{
		// Looks up a topic (identified by topicID) and returns the request message (identified by postID).
		readMessageHandler(request);
	}
}

/*
@brief The handle to deal with POST requests.
@param &ret - Socket data object -> Request data sent from the TCPclient.
*/
std::string RequestHandler::postMessageHandler(std::string request)
{
	postParser = postParser.parse(request);

	std::unique_lock<std::shared_mutex> uniqueLock(sharedMutex);

	if (messageBoard.find(postParser.getTopicId()) != messageBoard.end())
	{
		messageBoard.find(postParser.getTopicId())->second.emplace_back(postParser.getMessage());

		return std::to_string(messageBoard.find(postParser.getTopicId())->second.size() - 1);
	}
	else
	{
		std::vector<std::string> postMessageVector;

		postMessageVector.emplace_back(postParser.getMessage());

		messageBoard.insert({ postParser.getTopicId(), postMessageVector });

		return "0";
	}
}

/*
@brief The handle to deal with LIST requests.
@param &ret - Socket data object -> Request data sent from the TCPclient.
*/
std::string RequestHandler::listMessageHandler(std::string request)
{
	listParser = listParser.parse(request);

	// Multiple threads/readers can read the value at the same time.
	std::shared_lock<std::shared_mutex> sharedLock(sharedMutex);

	std::string topicListings;
	const std::string hashDivider("#");

	for (std::map<std::string, std::vector<std::string>>::iterator i = messageBoard.begin(); i != messageBoard.end(); i++)
	{
		// Ensure all topicIDs are separated by the "#" character as outlined in the protocol.html.
		topicListings.append(i->first).append(hashDivider);
	}

	// Remove the trailing # character.
	if (!topicListings.empty())
	{
		topicListings.pop_back();
	}
	return topicListings;
}

/*
@brief The handle to deal with COUNT requests.
@param &ret - Socket data object -> Request data sent from the TCPclient.
*/
std::string RequestHandler::countMessageHandler(std::string request)
{
	countParser = countParser.parse(request);

	// Multiple threads/readers can read the value at the same time.
	std::shared_lock<std::shared_mutex> sharedLock(sharedMutex);

	if (messageBoard.find(countParser.getTopicId()) != messageBoard.end())
	{
		// TopicID (Key in the Hashmap) has been found - Not returned the end of the data structure.
		// Parse the int to string.
		return std::to_string(messageBoard.find(countParser.getTopicId())->second.size());
	}
	else
	{
		// Topic does not exist - Return 0.
		return "0";
	}
}


/*
@brief The handle to deal with READ requests.
@param &ret - Socket data object -> Request data sent from the TCPclient.
*/
std::string RequestHandler::readMessageHandler(std::string request)
{
	readParser = readParser.parse(request);

	// Multiple threads/readers can read the value at the same time.
	std::shared_lock<std::shared_mutex> sharedLock(sharedMutex);

	if (messageBoard.find(readParser.getTopicId()) != messageBoard.end() && messageBoard.size() > 0 && messageBoard.find(readParser.getTopicId())->second.size() - 1 >= readParser.getPostId())
	{
		// TopicID (Key in the Hashmap) has been found - Not returned the end of the data structure.
		// MessageBoard is not empty (size must be greater than 0).
		// Message index exists -> The size-1 of the std::vector (matching a Vector that is 0-based index) is >= postID.
		return messageBoard.find(readParser.getTopicId())->second.at(readParser.getPostId());
	}
	else
	{
		// Respond with a blank line.
		return "";
	}
}



/*
@brief The handle to deal with EXIT|exit requests.
@param &ret - Socket data object -> Request data sent from the TCPclient.
*/
std::string RequestHandler::terminateRequestHandler(std::string request)
{
	exitParser = exitParser.parse(request);

	if (exitParser.valid)
	{
		return "TERMINATING";
	}
}