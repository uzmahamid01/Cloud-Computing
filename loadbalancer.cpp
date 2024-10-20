#include "loadbalancer.h"
#include <algorithm>

/**
 * @brief Constructs a LoadBalancer with a specified LogManager for logging.
 * 
 * @param logger Reference to a LogManager object used for logging activities.
 */
LoadBalancer::LoadBalancer(LogManager& logger)
    : logger(logger) {  
    initializeBlockedIpRanges();
}

/**
 * @brief Gets the current simulation time.
 * 
 * @return The current time as an integer.
 */
int LoadBalancer::getTime() const {
    return currentTime;
}

/**
 * @brief Increments the current simulation time by one unit.
 */
void LoadBalancer::incTime() {
    currentTime++;
}

/**
 * @brief Retrieves and removes the next request from the request queue.
 * 
 * @return The next Request object in the queue.
 */
Request LoadBalancer::getRequest() {
    return requestQueue.getRequest();
}

/**
 * @brief Checks if the request queue is empty.
 * 
 * @return True if the request queue is empty, false otherwise.
 */
bool LoadBalancer::isRequestQueueEmpty() const {
    return requestQueue.isEmpty();
}

/**
 * @brief Gets the size of the request queue.
 * 
 * @return The number of requests in the queue.
 */
size_t LoadBalancer::getRequestQueueSize() const {
    return requestQueue.size();
}

/**
 * @brief Gets the total number of processed requests.
 * 
 * @return The count of processed requests as an integer.
 */
int LoadBalancer::getProcessedRequests() const {
    return processedRequests;
}

/**
 * @brief Increments the count of processed requests by one.
 */
void LoadBalancer::incrementProcessedRequests() {
    processedRequests++;  // Increment the count of processed requests
}

/**
 * @brief Retrieves the next available server for processing requests.
 * 
 * @return A reference to the next WebServer object.
 */
WebServer& LoadBalancer::getNextServer() {
    WebServer& server = servers[currentServerIndex];
    currentServerIndex = (currentServerIndex + 1) % servers.size();
    return server;
}

/**
 * @brief Checks if a given IP address is blocked.
 * 
 * @param ip The IP address to check.
 * @return True if the IP address is blocked, false otherwise.
 */
bool LoadBalancer::isIpBlocked(const std::string& ip) const {
    for (const auto& range : blockedIpRanges) {
        if (ip.substr(0, range.length()) == range) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Gets the total number of rejected requests.
 * 
 * @return The count of rejected requests as an integer.
 */
int LoadBalancer::getRejectedRequests() const {
    return rejectedRequests;
}

/**
 * @brief Gets the total number of active servers.
 * 
 * @return The count of active servers as an integer.
 */
int LoadBalancer::getActiveServers() const {
    return activeServers;
}

/**
 * @brief Gets the total number of inactive servers.
 * 
 * @return The count of inactive servers as an integer.
 */
int LoadBalancer::getInactiveServers() const {
    return totalServers - activeServers;
}

/**
 * @brief Sets the total number of servers managed by the LoadBalancer.
 * 
 * @param total The total number of servers to set.
 */
void LoadBalancer::setTotalServers(int total) {
    totalServers = total;
}

/**
 * @brief Initializes the list of blocked IP ranges.
 */
void LoadBalancer::initializeBlockedIpRanges() {
    blockedIpRanges = {"192.168.0.", "10.0.0."};
}

/**
 * @brief Logs a rejected request for future analysis.
 * 
 * @param r The Request object that was rejected.
 */
void LoadBalancer::logRejectedRequest(const Request& r) {
    logger.log("Rejected request from IP: " + r.getIpIn());
}

/**
 * @brief Adds a request to the request queue.
 * 
 * This function checks if the IP of the request is blocked. If it is not blocked,
 * the request is added to the queue, and the processed request count is updated.
 * If the IP is blocked, the request is rejected, and the rejection is logged.
 * 
 * @param r The Request object to be added to the queue.
 */
void LoadBalancer::addRequest(const Request& r) {
    if (!isIpBlocked(r.getIpIn())) {
        requestQueue.addRequest(r);
        incrementProcessedRequests(); 
    } else {
        rejectedRequests++;
        logRejectedRequest(r);
    }
}

/**
 * @brief Allocates additional servers if needed based on the current request queue size.
 * 
 * A new server is allocated if the queue size exceeds five times the number of servers
 * and the total number of servers is below the maximum allowed.
 */
void LoadBalancer::allocateServer() {
    if (requestQueue.size() > static_cast<size_t>(servers.size()) * 5 && 
        servers.size() < static_cast<size_t>(maxServers)) {
        char newServerId = static_cast<char>('A' + servers.size());
        servers.emplace_back(newServerId);

        logger.log("Cycle: " + std::to_string(currentTime) + 
                   ", Server " + std::string(1, newServerId) + 
                   " allocated, Current Queue Size: " + std::to_string(requestQueue.size()));
    }
}

/**
 * @brief Deallocates servers that are no longer active based on the current request queue size.
 * 
 * A server is deallocated if the queue size is less than two times the number of servers
 * and the total number of servers is above the minimum required.
 */
void LoadBalancer::deallocateServer() {
    if (requestQueue.size() < static_cast<size_t>(servers.size()) * 2 && 
        servers.size() > static_cast<size_t>(minServers)) {
        char removedServerId = servers.back().getName();
        servers.pop_back();

        logger.log("Cycle: " + std::to_string(currentTime) + 
                   ", Server " + std::string(1, removedServerId) + 
                   " deallocated, Current Queue Size: " + std::to_string(requestQueue.size()));
    }
}
