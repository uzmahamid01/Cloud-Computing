#include "webserver.h"

/**
 * @brief Constructs a WebServer object with the specified name.
 * 
 * Initializes the server name, request start time, active request flag,
 * and processed request count.
 * 
 * @param name A character representing the server's name.
 */
WebServer::WebServer(char name) 
    : serverName(name), requestStartTime(0), hasActiveRequest(false), processedRequestCount(0) {}

/**
 * @brief Adds a request to the server.
 * 
 * This method assigns the given request to the server, sets the current
 * time for when the request starts processing, and updates the server's
 * active request status. It also adjusts the processing time based on the
 * job type (Processing or Streaming).
 * 
 * @param req The request to be added.
 * @param currTime The current time in clock cycles.
 */
void WebServer::addRequest(Request req, int currTime) {
    currentRequest = req;
    requestStartTime = currTime;
    hasActiveRequest = true;

    if (req.getJobType() == 'P') {
        // Processing jobs
    } else if (req.getJobType() == 'S') {
        requestStartTime += req.getProcessTime() / 2; 
    }
}

/**
 * @brief Checks if the current request is done processing.
 * 
 * This method evaluates whether the current request has completed processing
 * based on the job type and the current time.
 * 
 * @param currTime The current time in clock cycles.
 * @return True if the request is completed, false otherwise.
 */
bool WebServer::isRequestDone(int currTime) {
    if (hasActiveRequest) {
        if (currentRequest.getJobType() == 'P') {
            if (currTime >= requestStartTime + currentRequest.getProcessTime()) {
                hasActiveRequest = false; 
                return true;
            }
        } else if (currentRequest.getJobType() == 'S') {
            if (currTime >= requestStartTime + (currentRequest.getProcessTime() / 2)) {
                hasActiveRequest = false; 
                return true;
            }
        }
    }
    return false; 
}

/**
 * @brief Increments the count of processed requests.
 * 
 * This method increases the processed request count by one.
 */
void WebServer::incrementProcessedRequestCount() {
    ++processedRequestCount;
}

/**
 * @brief Retrieves the count of processed requests.
 * 
 * @return The total number of processed requests.
 */
int WebServer::getProcessedRequestCount() const {
    return processedRequestCount;
}

/**
 * @brief Checks if the server is currently idle.
 * 
 * @return True if the server has no active requests, false otherwise.
 */
bool WebServer::isIdle() const {
    return !hasActiveRequest;
}

/**
 * @brief Gets the name of the server.
 * 
 * @return The name of the server.
 */
char WebServer::getName() const {
    return serverName;
}
