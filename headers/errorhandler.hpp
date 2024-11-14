#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <stdexcept>
class log_err: public std::runtime_error
{
public:
    log_err(const std::string& s) : std::runtime_error(s) {}
    log_err(const char * s) : std::runtime_error(s) {}
};

class auth_err: public std::invalid_argument
{
public:
    auth_err(const std::string& s) : std::invalid_argument(s) {}
    auth_err(const char * s) : std::invalid_argument(s) {}
};
class read_err: public std::invalid_argument
{
public:
    read_err(const std::string& s) : std::invalid_argument(s) {}
    read_err(const char * s) : std::invalid_argument(s) {}
};
inline std::string logger(std::string lp, std::string what)
{
    std::string log_s;
    std::ofstream file(lp.c_str(), std::ios::app);
    if (file.is_open()) {
        std::time_t now = time(0);
        std::string date = std::ctime(&now);
        log_s = " - " + what + "\n";
        file << date+log_s;
        file.close();
    } else {
        throw log_err("Error opening log file");
    }
    return log_s;
}
