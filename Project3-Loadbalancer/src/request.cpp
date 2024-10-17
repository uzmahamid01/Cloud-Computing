#include "request.h"

/**
 * @brief Constructs a Request object with the specified parameters.
 * 
 * @param src The source address of the request.
 * @param dst The destination address of the request.
 * @param time The processing time for the request.
 * @param type The job type of the request ('P' for processing, 'H' for handling, etc.).
 * @param arrival The clock cycle when the request arrived.
 */
Request::Request(const std::string& src, const std::string& dst, int time, char type, int arrival)
    : source(src), destination(dst), processTime(time), jobType(type), arrivalTime(arrival) {}
