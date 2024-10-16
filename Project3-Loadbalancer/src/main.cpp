#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include "request.h"
#include "webserver.h"
#include "loadbalancer.h"

void simulateWebServer(WebServer& server, LoadBalancer& balancer) {
    while (true) {
        // Check if there's a request and process it
        if (!balancer.isRequestQueueEmpty()) {
            Request req = balancer.getRequest();
            server.addRequest(req, balancer.getTime());
            std::this_thread::sleep_for(std::chrono::milliseconds(req.processTime)); // Simulate processing time
            if (server.isRequestDone(balancer.getTime())) {
                std::cout << "Request processed by server " << server.getName() << std::endl;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Adjust this as needed
    }
}

int main() {
    int numServers, runTime;
    std::cout << "Enter number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter run time (in clock cycles): ";
    std::cin >> runTime;

    LoadBalancer loadBalancer;
    std::vector<WebServer> servers(numServers);

    // Create threads for each server
    std::vector<std::thread> serverThreads;
    for (int i = 0; i < numServers; ++i) {
        servers[i] = WebServer('A' + i); // Assign server names A, B, C, etc.
        serverThreads.emplace_back(simulateWebServer, std::ref(servers[i]), std::ref(loadBalancer));
    }

    // Generate initial requests and fill the load balancer queue
    for (int i = 0; i < numServers * 100; ++i) {
        std::string src = "192.168.1." + std::to_string(rand() % 256);
        std::string dst = "192.168.1." + std::to_string(rand() % 256);
        int processTime = rand() % 1000; // Random process time between 0 and 1000 ms
        char jobType = (rand() % 2 == 0) ? 'P' : 'S'; // Randomly assign job type P or S
        loadBalancer.addRequest(Request(src, dst, processTime, jobType));
    }

    // Simulate for a given runtime
    for (int clockCycle = 0; clockCycle < runTime; ++clockCycle) {
        loadBalancer.incTime();
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate a clock cycle delay
    }

    // Clean up threads (join them)
    for (auto& thread : serverThreads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    return 0;
}
