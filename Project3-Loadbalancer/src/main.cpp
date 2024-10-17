#include <iostream>
#include <fstream>
#include "request.h"
#include "webserver.h"
#include "requestqueue.h"
#include "loadbalancer.h"
#include <vector>
#include <cstdlib>
#include <ctime>

/**
 * @brief Main function for the Load Balancer simulation.
 * 
 * This function initializes the simulation, processes requests, 
 * and logs results to both console and file.
 * 
 * @return Exit status of the program.
 */
int main() {
    std::srand(std::time(nullptr)); // Seed for random number generation
    
    // Redirect stdout to a file
    freopen("output.log", "w", stdout);

    int numServers;               ///< Number of servers in the simulation
    int runTime;                  ///< Total simulation run time in clock cycles

    std::cout << "Enter number of servers: ";
    std::cin >> numServers;
    std::cout << "Enter the simulation run time (in clock cycles): ";
    std::cin >> runTime;

    // Log starting conditions
    std::cout << "Load Balancer Simulation Started." << std::endl;
    std::cout << "Number of servers: " << numServers << std::endl;
    std::cout << "Simulation run time (in clock cycles): " << runTime << std::endl;

    LoadBalancer lb;                         ///< Load Balancer instance
    std::vector<WebServer> servers;          ///< Vector of web servers

    for (int i = 0; i < numServers; ++i) {
        servers.push_back(WebServer('A' + i));
        std::cout << "Server " << static_cast<char>('A' + i) << " created." << std::endl;
    }

    std::vector<int> queue_size_over_time;  ///< Track queue size over time
    std::vector<int> request_wait_times;    ///< Track wait times for requests
    std::vector<int> requests_handled(servers.size(), 0); ///< Track requests handled by each server

    // Simulation loop
    for (int i = 0; i < runTime; ++i) {
        lb.incTime();
        int currentTime = lb.getTime();
        std::cout << "Clock cycle: " << currentTime << std::endl;

        // Process requests on servers
        for (auto& server : servers) {
            if (server.isRequestDone(currentTime)) {
                if (!lb.isRequestQueueEmpty()) {
                    Request req = lb.getRequest();
                    
                    // Find the least-loaded server
                    WebServer& leastLoadedServer = lb.getLeastLoadedServer(servers);
                    
                    // Assign the request to the least-loaded server
                    leastLoadedServer.addRequest(req, currentTime);
                    requests_handled[leastLoadedServer.getName() - 'A']++; // Track requests handled
                    std::cout << "Server " << leastLoadedServer.getName() << " processed request from "
                              << req.source << " to " << req.destination
                              << " with job type " << req.jobType << " at time " << currentTime << std::endl;
                    
                    // Track wait time
                    int waitTime = currentTime - req.arrivalTime;
                    request_wait_times.push_back(waitTime);
                }
            }
        }

        // Simulate new requests added randomly with dynamic timing
        if (std::rand() % 10 == 0) { // Randomly add a new request
            char jobType = (std::rand() % 2 == 0) ? 'P' : 'H';
            Request newRequest("192.168.1.1", "192.168.1.2", std::rand() % 100, jobType, currentTime);
            lb.addRequest(newRequest);
            std::cout << "New request added from " << newRequest.source << " to " << newRequest.destination
                      << " with job type " << newRequest.jobType << " at time " << currentTime << std::endl;
        }

        // Log queue size at each clock cycle
        int currentQueueSize = lb.getRequestQueueSize();
        queue_size_over_time.push_back(currentQueueSize);
        std::cout << "Queue size: " << currentQueueSize << std::endl;

        // Dynamically add or remove servers based on queue size
        if (currentQueueSize > 5 && servers.size() < 10) {
            char newServerName = 'A' + servers.size();
            servers.push_back(WebServer(newServerName));
            std::cout << "New Server " << newServerName << " added due to high queue size." << std::endl;
        } else if (currentQueueSize < 2 && servers.size() > 1) {
            char removedServerName = servers.back().getName();
            servers.pop_back();
            std::cout << "Server " << removedServerName << " removed due to low queue size." << std::endl;
        }
    }

    // Simulation ends
    std::cout << "Load Balancer Simulation Ended." << std::endl;

    // Calculate and display average request wait time
    if (!request_wait_times.empty()) {
        int total_wait_time = 0;
        for (int waitTime : request_wait_times) {
            total_wait_time += waitTime;
        }
        double average_wait_time = static_cast<double>(total_wait_time) / request_wait_times.size();
        std::cout << "Average request wait time: " << average_wait_time << " clock cycles" << std::endl;
    } else {
        std::cout << "No requests were handled." << std::endl;
    }

    // Output the queue size over time for analysis
    std::cout << "\nQueue size over time:\n";
    for (size_t i = 0; i < queue_size_over_time.size(); ++i) {
        std::cout << "Clock cycle " << i + 1 << ": Queue size = " << queue_size_over_time[i] << std::endl;
    }

    // Output the requests handled by each server
    std::cout << "\nRequests handled by each server:\n";
    for (size_t i = 0; i < servers.size(); ++i) {
        std::cout << "Server " << servers[i].getName() << ": " << requests_handled[i] << " requests handled." << std::endl;
    }

    // Add at the top of your main function
    std::ofstream outputFile("simulation_results.csv");

    // Write header
    outputFile << "Clock Cycle,Queue Size\n";

    // After the simulation loop
    for (size_t i = 0; i < queue_size_over_time.size(); ++i) {
        outputFile << i + 1 << "," << queue_size_over_time[i] << "\n";
    }

    // Write requests handled
    outputFile << "Server,Requests Handled\n";
    for (size_t i = 0; i < servers.size(); ++i) {
        outputFile << servers[i].getName() << "," << requests_handled[i] << "\n";
    }

    // Close the file
    outputFile.close();

    return 0;
}
