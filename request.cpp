#include "request.h"

/**
 * @brief Default constructor for Request.
 * 
 * Initializes a Request object with default values: empty IP addresses,
 * a processing time of 0, an undefined job type, and an arrival time of 0.
 */
Request::Request() : ipIn(""), ipOut(""), processTime(0), jobType(' '), arrivalTime(0) {}

/**
 * @brief Parameterized constructor for Request.
 * 
 * Initializes a Request object with the specified input IP, output IP,
 * processing time, job type, and arrival time.
 * 
 * @param ip_in The input IP address for the request.
 * @param ip_out The output IP address for the request.
 * @param time The processing time for the request.
 * @param type The job type (character P for processing, S for streaming).
 * @param arrival The arrival time of the request.
 */
Request::Request(const std::string& ip_in, const std::string& ip_out, int time, char type, int arrival)
    : ipIn(ip_in), ipOut(ip_out), processTime(time), jobType(type), arrivalTime(arrival) {}

/**
 * @brief Gets the input IP address of the request.
 * 
 * @return The input IP address as a string.
 */
std::string Request::getIpIn() const { return ipIn; }

/**
 * @brief Gets the output IP address of the request.
 * 
 * @return The output IP address as a string.
 */
std::string Request::getIpOut() const { return ipOut; }

/**
 * @brief Gets the processing time of the request.
 * 
 * @return The processing time as an integer.
 */
int Request::getProcessTime() const { return processTime; }

/**
 * @brief Gets the job type of the request.
 * 
 * @return The job type as a character.
 */
char Request::getJobType() const { return jobType; }

/**
 * @brief Gets the arrival time of the request.
 * 
 * @return The arrival time as an integer.
 */
int Request::getArrivalTime() const { return arrivalTime; }
