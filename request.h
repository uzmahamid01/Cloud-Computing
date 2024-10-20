#ifndef REQUEST_H
#define REQUEST_H

#include <string>

 //all doxygen comments are generated with AI assistance


/**
 * @brief A class to represent a network request.
 * 
 * The Request class encapsulates the details of a network request, including 
 * the input and output IP addresses, processing time, job type, and arrival time.
 */
class Request {
public:
    /**
     * @brief Default constructor for Request.
     * 
     * Initializes a Request object with default values.
     */
    Request();

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
    Request(const std::string& ip_in, const std::string& ip_out, int time, char type, int arrival);

    /**
     * @brief Gets the input IP address of the request.
     * 
     * @return The input IP address as a string.
     */
    std::string getIpIn() const;

    /**
     * @brief Gets the output IP address of the request.
     * 
     * @return The output IP address as a string.
     */
    std::string getIpOut() const;

    /**
     * @brief Gets the processing time of the request.
     * 
     * @return The processing time as an integer.
     */
    int getProcessTime() const;

    /**
     * @brief Gets the job type of the request.
     * 
     * @return The job type as a character.
     */
    char getJobType() const;

    /**
     * @brief Gets the arrival time of the request.
     * 
     * @return The arrival time as an integer.
     */
    int getArrivalTime() const;

private:
    std::string ipIn;        ///< The input IP address for the request.
    std::string ipOut;       ///< The output IP address for the request.
    int processTime;         ///< The processing time for the request.
    char jobType;            ///< The job type (P for processing, S for streaming).
    int arrivalTime;         ///< The arrival time of the request.
};

#endif
