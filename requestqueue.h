#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "request.h"
#include <queue>

 //all doxygen comments are generated with AI assistance


/**
 * @brief A class to represent a queue of requests.
 * 
 * The RequestQueue class manages a queue of Request objects, allowing 
 * requests to be added, retrieved, and checked for size and emptiness.
 */
class RequestQueue {
public:
    /**
     * @brief Adds a request to the queue.
     * 
     * This method inserts the specified request into the queue for later processing.
     * 
     * @param r The request to be added to the queue.
     */
    void addRequest(const Request& r);
    
    /**
     * @brief Retrieves and removes a request from the queue.
     * 
     * This method returns the front request from the queue and removes it from the queue.
     * 
     * @return The request at the front of the queue.
     */
    Request getRequest();
    
    /**
     * @brief Checks if the queue is empty.
     * 
     * This method determines whether the queue contains any requests.
     * 
     * @return True if the queue is empty, false otherwise.
     */
    bool isEmpty() const;
    
    /**
     * @brief Gets the current size of the queue.
     * 
     * This method returns the number of requests currently in the queue.
     * 
     * @return The number of requests in the queue.
     */
    size_t size() const;

private:
    std::queue<Request> queue; ///< The underlying queue storing Request objects.
};

#endif
