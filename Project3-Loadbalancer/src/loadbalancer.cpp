#include "loadbalancer.h"

// Constructor
LoadBalancer::LoadBalancer() : systemTime(0) {}

// Get current system time
int LoadBalancer::getTime() {
    return systemTime;
}

// Increment the system time
void LoadBalancer::incTime() {
    systemTime++;
}

// Add request to the queue
void LoadBalancer::addRequest(Request r) {
    requestQueue.addRequest(r);
    incTime();
}

// Get the next request from the queue
Request LoadBalancer::getRequest() {
    incTime();
    return requestQueue.getRequest();
}

// Check if the request queue is empty
bool LoadBalancer::isRequestQueueEmpty() {
    return requestQueue.isEmpty();
}
