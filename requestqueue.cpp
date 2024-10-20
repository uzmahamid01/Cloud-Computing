#include "requestqueue.h"

/**
 * @brief Adds a request to the queue.
 * 
 * This method inserts the specified request into the queue for later processing.
 * 
 * @param r The request to be added to the queue.
 */
void RequestQueue::addRequest(const Request& r) {
    queue.push(r);
}

/**
 * @brief Retrieves and removes a request from the queue.
 * 
 * This method returns the front request from the queue and removes it from the queue.
 * If the queue is empty, it returns a default-constructed Request object.
 * 
 * @return The request at the front of the queue, or a default Request if the queue is empty.
 */
Request RequestQueue::getRequest() {
    if (!queue.empty()) {
        Request r = queue.front();
        queue.pop();
        return r;
    }
    return Request(); // Return a default-constructed Request if the queue is empty.
}

/**
 * @brief Checks if the queue is empty.
 * 
 * This method determines whether the queue contains any requests.
 * 
 * @return True if the queue is empty, false otherwise.
 */
bool RequestQueue::isEmpty() const {
    return queue.empty();
}

/**
 * @brief Gets the current size of the queue.
 * 
 * This method returns the number of requests currently in the queue.
 * 
 * @return The number of requests in the queue.
 */
size_t RequestQueue::size() const {
    return queue.size();
}
