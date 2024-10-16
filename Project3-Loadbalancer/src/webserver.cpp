#include "webserver.h"

WebServer::WebServer() : r("", "", 0, ' ') {  
    requestStartTime = 0;
    serverName = ' ';
}

WebServer::WebServer(char c) : r("", "", 0, ' ') {  
    requestStartTime = 0;
    serverName = c;
}

void WebServer::addRequest(Request req, int currTime) {
    r = req;                     // Assign the incoming request
    requestStartTime = currTime;  // Record the time the request was added
}

Request WebServer::getRequest() {
    return r;  // Return the request being processed
}

char WebServer::getName() {
    return serverName;  // Return the server's name
}

bool WebServer::isRequestDone(int currTime) {
    // Check if the request is done by comparing current time with process time
    return (currTime > requestStartTime + r.processTime);
}
