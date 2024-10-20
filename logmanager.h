// logmanager.h
#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <fstream>
#include <string>


class LogManager {
public:
    LogManager(const std::string& filename);
    ~LogManager();

    void log(const std::string& message);

private:
    std::ofstream logFile;
};

#endif