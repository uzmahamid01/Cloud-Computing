#include "requestqueue.h"

// Constructor
RequestQueue::RequestQueue() {}

// Add a request to the queue
void RequestQueue::addRequest(const Request& r) {
    queue.push(r);
}

// Get the next request from the queue
Request RequestQueue::getRequest() {
    if (!queue.empty()) {
        Request r = queue.front();
        queue.pop();
        return r;
    }
    return Request("", "", 0, ' ');
}

// Check if the queue is empty
bool RequestQueue::isEmpty() const {
    return queue.empty();
}

// Get the size of the queue
int RequestQueue::size() const {
    return queue.size();
}
