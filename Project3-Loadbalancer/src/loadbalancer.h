#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "request.h"
#include "requestqueue.h"

// LoadBalancer class
class LoadBalancer {
public:
    LoadBalancer();                // Constructor
    int getTime();                 // Get current system time
    void incTime();                // Increment the system time
    void addRequest(Request r);    // Add request to the queue
    Request getRequest();          // Get the next request from the queue
    bool isRequestQueueEmpty();    // Check if the request queue is empty
    bool allRequestsProcessed() const; // Check if all requests have been processed

private:
    int systemTime;                // System time
    RequestQueue requestQueue;     // Queue to store requests
    int totalRequests;             // Track total requests added
    int processedRequests;         // Track processed requests
};

#endif // LOADBALANCER_H
