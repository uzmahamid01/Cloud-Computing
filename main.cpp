#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "loadbalancer.h"
#include "webserver.h"
#include "logmanager.h"
#include <sstream>
#include <iomanip>

 //all doxygen comments are generated with AI assistance


/**
 * @brief Generates a random IP address.
 * 
 * This function generates a random IP address in the format of
 * x.x.x.x where x is a number between 0 and 255.
 * 
 * @return A string representing a randomly generated IP address.
 */

std::string generateRandomIP() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    return std::to_string(dis(gen)) + "." + std::to_string(dis(gen)) + "." +
           std::to_string(dis(gen)) + "." + std::to_string(dis(gen));
}

/**
 * @brief Main function for the load balancer simulation.
 * 
 * This function initializes the load balancer, accepts user input
 * for the number of servers and runtime, generates initial requests,
 * and runs the simulation for the specified clock cycles.
 * It logs the status of the load balancer, servers, and requests
 * during the simulation.
 * 
 * @return int Status code of the program (0 for success).
 */

int main() {
    int numServers, runTime;
    std::cout << "Enter the number of initial servers: ";
    std::cin >> numServers;
    std::cout << "Enter the time to run the load balancer (in clock cycles): ";
    std::cin >> runTime;

    LogManager logger("load_balancer_log.txt"); ///< Logger instance for recording simulation events
    LoadBalancer loadBalancer(logger);           ///< LoadBalancer instance to manage request handling
    std::vector<WebServer> servers;               ///< Vector to hold the web servers

    logger.log("");
    logger.log("-------------------Simulation Starts-----------------------------");
    logger.log("");

    for (int i = 0; i < numServers; ++i) {
        servers.emplace_back(static_cast<char>('A' + i));
    }

    int initialRequests = numServers * 100;
    int startingQueueSize = 0; 
    int minProcessTime = INT_MAX; 
    int maxProcessTime = INT_MIN; 

    for (int i = 0; i < initialRequests; ++i) {
        std::string ipIn = generateRandomIP();
        std::string ipOut = generateRandomIP();
        int processTime = std::rand() % 50 + 1; // 1 to 50 clock cycles
        char jobType = (std::rand() % 2 == 0) ? 'P' : 'S';
        
        minProcessTime = std::min(minProcessTime, processTime);
        maxProcessTime = std::max(maxProcessTime, processTime);
        
        Request req(ipIn, ipOut, processTime, jobType, loadBalancer.getTime());
        loadBalancer.addRequest(req);
        
        logger.log("Clock Cycle: 0, Initial Request: " + req.getIpIn() + " -> " + req.getIpOut() + ", Process Time: " + std::to_string(processTime) + ", Job Type: " + jobType);
    }

    startingQueueSize = loadBalancer.getRequestQueueSize();
    logger.log("");
    logger.log("------------------------------------------------");
    logger.log("Starting Queue Size: " + std::to_string(startingQueueSize));
    logger.log("------------------------------------------------");
    logger.log("");

    while (loadBalancer.getTime() < runTime) {
        for (auto& server : servers) {
            if (server.isIdle()) {
                if (!loadBalancer.isRequestQueueEmpty()) {
                    Request req = loadBalancer.getRequest();
                    server.addRequest(req, loadBalancer.getTime());
                    logger.log("Clock Cycle: " + std::to_string(loadBalancer.getTime()) + ", Server " + server.getName() + " handling request from " + req.getIpIn() + " to " + req.getIpOut() + ", Job Type: " + req.getJobType());
                }
            } else if (server.isRequestDone(loadBalancer.getTime())) {
                loadBalancer.incrementProcessedRequests();
                server.incrementProcessedRequestCount();
                logger.log("Clock Cycle: " + std::to_string(loadBalancer.getTime()) + ", Server " + server.getName() + " completed request.");

                if (!loadBalancer.isRequestQueueEmpty()) {
                    Request req = loadBalancer.getRequest();
                    server.addRequest(req, loadBalancer.getTime());
                    logger.log("Clock Cycle: " + std::to_string(loadBalancer.getTime()) + ", Server " + server.getName() + " handling new request from " + req.getIpIn() + " to " + req.getIpOut() + ", Job Type: " + req.getJobType());
                }
            }
        }

        //dynamic server allocation and deallocation
        loadBalancer.allocateServer();
        loadBalancer.deallocateServer();

        //generate new requests randomly
        if (std::rand() % 10 == 0) {
            std::string ipIn = generateRandomIP();
            std::string ipOut = generateRandomIP();
            int processTime = std::rand() % 50 + 1;
            char jobType = (std::rand() % 2 == 0) ? 'P' : 'S';

            minProcessTime = std::min(minProcessTime, processTime);
            maxProcessTime = std::max(maxProcessTime, processTime);

            Request req(ipIn, ipOut, processTime, jobType, loadBalancer.getTime());
            loadBalancer.addRequest(req);
            
            logger.log("Clock Cycle: " + std::to_string(loadBalancer.getTime()) + ", New Request: " + req.getIpIn() + " -> " + req.getIpOut() + ", Process Time: " + std::to_string(processTime) + ", Job Type: " + jobType);
        }

        loadBalancer.incTime();
    }

    logger.log("");
    logger.log("-------------------Simulation Completed-----------------------------");
    logger.log("");

    // simulation completion details
    std::stringstream ss;
    ss << "Final status:" << std::endl
       << "  Total servers: " << servers.size() << std::endl
       << "  Requests in queue: " << loadBalancer.getRequestQueueSize() << std::endl
       << "  Total requests processed: " << loadBalancer.getProcessedRequests() << std::endl
       << "  Active servers: " << loadBalancer.getActiveServers() << std::endl
       << "  Inactive servers: " << loadBalancer.getInactiveServers() << std::endl
       << "  Rejected/discarded requests: " << loadBalancer.getRejectedRequests() << std::endl
       << "  Ending Queue Size: " << loadBalancer.getRequestQueueSize() << std::endl 
       << "  Task Time Range: " << minProcessTime << " to " << maxProcessTime; 

    logger.log(ss.str());

    logger.log("");
    logger.log("------------------------------------------------");
    logger.log("");

    logger.log("Requests handled by each server:");    

    for (const auto& server : servers) {
        std::stringstream serverStats;   
        serverStats << "  Server " << server.getName() << ": " << server.getProcessedRequestCount();
        logger.log(serverStats.str());
    }
}
