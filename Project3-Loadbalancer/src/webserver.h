#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"  

/**
 * @brief Class representing a web server that processes requests.
 */
class WebServer {
public:
    /**
     * @brief Default constructor that initializes a WebServer with default parameters.
     */
    WebServer();               

    /**
     * @brief Constructor that initializes a WebServer with a specified server name.
     * 
     * @param c Character representing the server name.
     */
    WebServer(char c);          

    /**
     * @brief Adds a request to the server.
     * 
     * @param req The request to be added.
     * @param currTime The current time when the request is added.
     */
    void addRequest(Request req, int currTime);  

    /**
     * @brief Retrieves the current request being processed by the server.
     * 
     * @return The current request.
     */
    Request getRequest();       

    /**
     * @brief Gets the name of the server.
     * 
     * @return The server's name as a character.
     */
    char getName();             

    /**
     * @brief Checks if the current request has completed processing.
     * 
     * @param currTime The current time to compare against the request's process time.
     * @return True if the request is done, false otherwise.
     */
    bool isRequestDone(int currTime); 

    /**
     * @brief Gets the count of active requests being processed by the server.
     * 
     * @return The number of active requests.
     */
    int getActiveRequests() const;  

    /**
     * @brief Decrements the active requests counter when a request is finished.
     */
    void finishRequest(); 

    /**
     * @brief Gets the server ID based on the server name.
     * 
     * @return The server ID as an integer.
     */
    int getId() const { return static_cast<int>(serverName ); } 

private:
    Request r;                  
    int requestStartTime;        
    char serverName;            
    int activeRequests;          
};

#endif 
