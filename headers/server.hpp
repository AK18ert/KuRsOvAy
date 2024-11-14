

#pragma once
#include <cstdlib> 
#include <cstring> 
#include <unistd.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <bitset>
#include <cstdint>
#include <limits>
#include <iomanip>


class server
{
private:
	std::string lp;
	int sckt;
    int wrkr;
    int rc;
    char *buf = new char[4096];
    std::map <std::string, std::string> userdata;
public:
    server(std::string fpath, int port, std::string lpath);
    bool authentication();
    bool handling();
    int start(int port, const char* address);
	int accepting_connection();
	void logMessage(const std::string& message);
};