/**
 * @file webserver.h
 *
 * This file contains the definition of the WebServer class, which manages
 * requests received from the load balancer, processes them, and tracks
 * performance metrics.
 */

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"

 //all doxygen comments are generated with AI assistance

/**
 * @class WebServer
 * @brief A class to represent a server that processes a request
 *
 * The WebServer class handles incoming requests, processes them, and keeps
 * track of the number of requests processed.
 */
class WebServer {
public:
    /**
     * @brief Constructs a WebServer with a specified name.
     * @param name A character representing the server's name.
     */
    WebServer(char name);

    /**
     * @brief Adds a request to the server's queue.
     * @param req The request to be added.
     * @param currTime The current time in clock cycles.
     */
    void addRequest(Request req, int currTime);       //implemented with the assistance of AI

    /**
     * @brief Checks if the current request is done processing.
     * @param currTime The current time in clock cycles.
     * @return True if the request is completed, false otherwise.
     */
    bool isRequestDone(int currTime);

    /**
     * @brief Checks if the server is currently idle.
     * @return True if the server has no active requests, false otherwise.
     */
    bool isIdle() const;       //implemented with the assistance of AI

    /**
     * @brief Gets the name of the server.
     * @return The server's name.
     */
    char getName() const;

    /**
     * @brief Increments the count of processed requests.
     */
    void incrementProcessedRequestCount();

    /**
     * @brief Gets the count of processed requests.
     * @return The total number of processed requests.
     */
    int getProcessedRequestCount() const;

private:
    char serverName; ///< The name of the server.
    Request currentRequest; ///< The request currently being processed.
    int requestStartTime; ///< The time when the current request started processing.
    bool hasActiveRequest = false; ///< Flag indicating if there is an active request.
    int processedRequestCount = 0; ///< Count of processed requests.
};

#endif
