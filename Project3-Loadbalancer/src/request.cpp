#include "request.h"

Request::Request(const std::string& src, const std::string& dst, int time, char type): source(src), destination(dst), processTime(time), jobType(type){} 
