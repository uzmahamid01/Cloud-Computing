#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "request.h"
#include "requestqueue.h"
#include "webserver.h"
#include "logmanager.h"
#include <vector>
#include <string>

 //all doxygen comments are generated with AI assistance
/**
 * @class LoadBalancer
 * @brief Manages incoming requests and distributes them among a set of web servers.
 * 
 * The LoadBalancer is responsible for queuing incoming requests, managing server allocation,
 * monitoring server statuses, and logging information about processed and rejected requests.
 */
class LoadBalancer {
public:
    /**
     * @brief Constructs a LoadBalancer with a specified LogManager for logging.
     * 
     * @param logger Reference to a LogManager object used for logging activities.
     */
    LoadBalancer(LogManager& logger);

    /**
     * @brief Gets the current simulation time.
     * 
     * @return The current time as an integer.
     */
    int getTime() const;

    /**
     * @brief Increments the current simulation time by one unit.
     */
    void incTime();


    /**
     * @brief Adds a request to the request queue.
     * 
     * @param r The Request object to be added to the queue.
     */
    void addRequest(const Request& r);

    /**
     * @brief Retrieves and removes the next request from the request queue.
     * 
     * @return The next Request object in the queue.
     */
    Request getRequest();

    /**
     * @brief Checks if the request queue is empty.
     * 
     * @return True if the request queue is empty, false otherwise.
     */
    bool isRequestQueueEmpty() const;

    /**
     * @brief Gets the size of the request queue.
     * 
     * @return The number of requests in the queue.
     */
    size_t getRequestQueueSize() const;

    /**
     * @brief Gets the total number of processed requests.
     * 
     * @return The count of processed requests as an integer.
     */
    int getProcessedRequests() const;


    /**
     * @brief Increments the count of processed requests by one.
     */
    void incrementProcessedRequests();


    /**
     * @brief Retrieves the next available server for processing requests.
     * 
     * @return A reference to the next WebServer object.
     */
    WebServer& getNextServer();

    /**
     * @brief Allocates additional servers if needed.
     */
    void allocateServer();

    /**
     * @brief Deallocates servers that are no longer active.
     */
    void deallocateServer();

    // IP blocking

    /**
     * @brief Checks if a given IP address is blocked.
     * 
     * @param ip The IP address to check.
     * @return True if the IP address is blocked, false otherwise.
     */
    bool isIpBlocked(const std::string& ip) const;   //implemented with the assistance of AI


    /**
     * @brief Gets the total number of rejected requests.
     * 
     * @return The count of rejected requests as an integer.
     */
    int getRejectedRequests() const;

    /**
     * @brief Gets the total number of active servers.
     * 
     * @return The count of active servers as an integer.
     */
    int getActiveServers() const;

    /**
     * @brief Gets the total number of inactive servers.
     * 
     * @return The count of inactive servers as an integer.
     */
    int getInactiveServers() const;

    /**
     * @brief Sets the total number of servers managed by the LoadBalancer.
     * 
     * @param total The total number of servers to set.
     */
    void setTotalServers(int total);

private:
    LogManager& logger;  /**< Reference to the LogManager used for logging. */
    int currentTime = 0; /**< Current simulation time. */
    RequestQueue requestQueue; /**< Queue to manage incoming requests. */
    int currentServerIndex = 0; /**< Index of the currently allocated server. */
    int processedRequests = 0; /**< Total number of processed requests. */
    int rejectedRequests = 0; /**< Total number of rejected requests. */
    int activeServers = 0; /**< Current number of active servers. */
    int totalServers = 0; /**< Total number of servers managed. */

    const int maxServers = 50; /**< Maximum number of servers allowed. */
    const int minServers = 10; /**< Minimum number of servers required. */

   
    std::vector<std::string> blockedIpRanges; /**< List of blocked IP ranges. */
    std::vector<WebServer> servers; /**< List of web servers managed by the LoadBalancer. */

    /**
     * @brief Initializes the list of blocked IP ranges.
     */
    void initializeBlockedIpRanges();        //implemented with the assistance of AI

    /**
     * @brief Logs a rejected request for future analysis.
     * 
     * @param r The Request object that was rejected.
     */
    void logRejectedRequest(const Request& r);         //implemented with the assistance of AI
};

#endif // LOADBALANCER_H
