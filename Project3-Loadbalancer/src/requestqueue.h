#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "request.h"
#include <queue>

// RequestQueue class
class RequestQueue {
public:
    RequestQueue();               // Constructor
    void addRequest(const Request& r);  // Add a request to the queue
    Request getRequest();         // Get the next request from the queue
    bool isEmpty() const;         // Check if the queue is empty
    int size() const;             // Get the size of the queue

private:
    std::queue<Request> queue;    // Internal queue to store requests
};

#endif // REQUESTQUEUE_H
