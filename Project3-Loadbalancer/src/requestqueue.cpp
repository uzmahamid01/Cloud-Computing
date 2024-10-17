#include "requestqueue.h"

/**
 * @brief Constructs an empty RequestQueue.
 */
RequestQueue::RequestQueue() {}

/**
 * @brief Adds a request to the queue.
 * 
 * @param r The request to be added to the queue.
 */
void RequestQueue::addRequest(const Request& r) {
    queue.push(r);  
}

/**
 * @brief Retrieves and removes the next request from the queue.
 * 
 * @return The next request in the queue. If the queue is empty,
 *         a default Request object with arrivalTime set to 0 is returned.
 */
Request RequestQueue::getRequest() {
    if (!queue.empty()) {
        Request r = queue.front();
        queue.pop();
        return r;
    }
    return Request("", "", 0, ' ', 0);  
}

/**
 * @brief Checks if the request queue is empty.
 * 
 * @return True if the queue is empty, false otherwise.
 */
bool RequestQueue::isEmpty() const {
    return queue.empty();
}

/**
 * @brief Gets the number of requests in the queue.
 * 
 * @return The size of the request queue.
 */
int RequestQueue::size() const {
    return queue.size();
}
