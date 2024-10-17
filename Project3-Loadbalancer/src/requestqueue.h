#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "request.h"
#include <queue>

/**
 * @brief Manages a queue of requests.
 */
class RequestQueue {
public:
    /**
     * @brief Constructs an empty RequestQueue.
     */
    RequestQueue();

    /**
     * @brief Adds a request to the queue.
     * 
     * @param r The request to be added to the queue.
     */
    void addRequest(const Request& r);

    /**
     * @brief Retrieves and removes the next request from the queue.
     * 
     * @return The next request in the queue.
     */
    Request getRequest();

    /**
     * @brief Checks if the request queue is empty.
     * 
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * @brief Gets the number of requests in the queue.
     * 
     * @return The size of the request queue.
     */
    int size() const;

private:
    std::queue<Request> queue;   
};

#endif 
