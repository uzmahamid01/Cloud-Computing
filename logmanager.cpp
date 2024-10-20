// logmanager.cpp
#include "logmanager.h"
#include <iostream>

LogManager::LogManager(const std::string& filename) {
    logFile.open(filename);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

LogManager::~LogManager() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void LogManager::log(const std::string& message) {
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}

