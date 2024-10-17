#ifndef REQUEST_H   
#define REQUEST_H

#include <string>   

/**
 * @brief Represents a network request.
 * 
 * The Request structure contains information about a request including
 * its source and destination, processing time, job type, and arrival time.
 */
struct Request {    
    std::string source;      
    std::string destination; 
    int processTime;         
    char jobType;            
    int arrivalTime;         

    /**
     * @brief Constructs a Request object with the specified parameters.
     * 
     * @param src The source address of the request.
     * @param dst The destination address of the request.
     * @param time The processing time for the request.
     * @param type The job type of the request.
     * @param arrival The clock cycle when the request arrived.
     */
    Request(const std::string& src, const std::string& dst, int time, char type, int arrival);
    
};

#endif 
