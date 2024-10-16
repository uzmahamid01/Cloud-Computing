#ifndef REQUEST_H   
#define REQUEST_H

#include <string>   

struct Request {    
    std::string source;      
    std::string destination;  
    int processTime;          
    char jobType;        

    // constructor
    Request(const std::string& src, const std::string& dst, int time, char type);
    
};


#endif 
