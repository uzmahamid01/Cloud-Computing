#include "webserver.h"

/**
 * @brief Constructs a WebServer with default parameters.
 */
WebServer::WebServer() : r("", "", 0, ' ', 0) {  
    requestStartTime = 0;
    serverName = ' ';
    activeRequests = 0;
}

/**
 * @brief Constructs a WebServer with a specified name.
 * 
 * @param c Character representing the server name.
 */
WebServer::WebServer(char c) : r("", "", 0, ' ', 0) {  
    requestStartTime = 0;
    serverName = c;
    activeRequests = 0;
}

/**
 * @brief Adds a request to the server.
 * 
 * @param req The request to be added.
 * @param currTime The current time when the request is added.
 */
void WebServer::addRequest(Request req, int currTime) {
    r = req;                     
    requestStartTime = currTime;  
    activeRequests++;
}

/**
 * @brief Retrieves the request being processed by the server.
 * 
 * @return The current request.
 */
Request WebServer::getRequest() {
    return r;  
}

/**
 * @brief Gets the name of the server.
 * 
 * @return The server's name.
 */
char WebServer::getName() {
    return serverName;  
}

/**
 * @brief Checks if the current request is done processing.
 * 
 * @param currTime The current time to compare against the request's process time.
 * @return True if the request is done, false otherwise.
 */
bool WebServer::isRequestDone(int currTime) {
    if (currTime > requestStartTime + r.processTime) {
        finishRequest();          
        return true;
    }
    return false;
}

/**
 * @brief Gets the number of active requests being processed by the server.
 * 
 * @return The count of active requests.
 */
int WebServer::getActiveRequests() const {
    return activeRequests; 
}

/**
 * @brief Decrements the active requests counter when a request is finished.
 */
void WebServer::finishRequest() {
    activeRequests--;  
}
