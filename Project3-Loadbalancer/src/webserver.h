#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "request.h"  // Ensure Request structure is defined

class WebServer {
public:
    WebServer();               // Default constructor
    WebServer(char c);          // Constructor with a server name

    void addRequest(Request req, int currTime);  // Add request to the server
    Request getRequest();       // Get the current request
    char getName();             // Get server name
    bool isRequestDone(int currTime);  // Check if the request is done

private:
    Request r;                  // The request being processed
    int requestStartTime;        // Time when the request started
    char serverName;             // Name of the server (character)
};

#endif // WEBSERVER_H
