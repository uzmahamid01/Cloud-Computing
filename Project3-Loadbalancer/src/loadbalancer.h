#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "request.h"
#include "requestqueue.h"
#include "webserver.h"

/**
 * @class LoadBalancer
 * @brief Manages the load balancing of web servers and request handling.
 */
class LoadBalancer {
public:
    /**
     * @brief Constructs a LoadBalancer object and initializes the current time.
     */
    LoadBalancer();

    /**
     * @brief Gets the current system time.
     * @return The current time in clock cycles.
     */
    int getTime();

    /**
     * @brief Increments the system time by one clock cycle.
     */
    void incTime();

    /**
     * @brief Adds a request to the queue.
     * @param r The request to be added.
     */
    void addRequest(Request r);

    /**
     * @brief Gets the next request from the queue.
     * @return The next request from the queue.
     */
    Request getRequest();

    /**
     * @brief Checks if the request queue is empty.
     * @return True if the queue is empty, false otherwise.
     */
    bool isRequestQueueEmpty();

    /**
     * @brief Checks if all requests have been processed.
     * @return True if all requests have been processed, false otherwise.
     */
    bool allRequestsProcessed() const;

    /**
     * @brief Gets the least loaded server from the list of servers.
     * @param servers A vector of web servers.
     * @return A reference to the least loaded WebServer.
     */
    WebServer& getLeastLoadedServer(std::vector<WebServer>& servers);

    /**
     * @brief Gets the current size of the request queue.
     * @return The number of requests in the queue.
     */
    int getRequestQueueSize() const;

private:
    int currentTime;               ///< Current system time in clock cycles.
    RequestQueue requestQueue;     ///< Queue to hold incoming requests.
    int totalRequests;             ///< Total number of requests added to the queue.
    int processedRequests;         ///< Number of requests that have been processed.
};

#endif // LOADBALANCER_H
