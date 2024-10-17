#include "loadbalancer.h"
#include "webserver.h"

/**
 * @brief Constructs a LoadBalancer object and initializes the current time to 0.
 */
LoadBalancer::LoadBalancer() : currentTime(0) {}

/**
 * @brief Gets the current system time.
 * 
 * @return The current time in clock cycles.
 */
int LoadBalancer::getTime() {
    return currentTime;
}

/**
 * @brief Increments the system time by one clock cycle.
 */
void LoadBalancer::incTime() {
    currentTime++;
}

/**
 * @brief Adds a request to the request queue and increments the system time.
 * 
 * @param r The request to be added to the queue.
 */
void LoadBalancer::addRequest(Request r) {
    requestQueue.addRequest(r);
    incTime();
}

/**
 * @brief Retrieves the next request from the request queue and increments the system time.
 * 
 * @return The next request in the queue.
 */
Request LoadBalancer::getRequest() {
    incTime();
    return requestQueue.getRequest();
}

/**
 * @brief Checks if the request queue is empty.
 * 
 * @return True if the request queue is empty, false otherwise.
 */
bool LoadBalancer::isRequestQueueEmpty() {
    return requestQueue.isEmpty();
}

/**
 * @brief Finds the least loaded server from a vector of servers.
 * 
 * @param servers A vector of WebServer objects to check for load balancing.
 * 
 * @return A reference to the least loaded WebServer.
 */
WebServer& LoadBalancer::getLeastLoadedServer(std::vector<WebServer>& servers) {
    WebServer* leastLoadedServer = &servers[0];  

    for (auto& server : servers) {
        if (server.getActiveRequests() < leastLoadedServer->getActiveRequests()) {
            leastLoadedServer = &server;
        }
    }
    return *leastLoadedServer;
}

/**
 * @brief Gets the size of the request queue.
 * 
 * @return The number of requests currently in the queue.
 */
int LoadBalancer::getRequestQueueSize() const {
    return requestQueue.size();
}
