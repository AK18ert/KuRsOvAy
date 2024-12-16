/** @file server.hpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Класс, управляющий работой сервера
 * @date 21.12.2023
 * @copyright ИБСТ ПГУ
 */

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

/**
 * @brief Класс управления работой сервера
 */
 
class server
{
private:
	int port;
	const char* address;
	std::string lp;
	int sckt;
    int wrkr;
    int rc;
    char *buf = new char[4096];
    std::map <std::string, std::string> userdata;
	int start();
public:
    server(std::string fpath, int port, std::string lpath);
    bool authentication();
    bool handling();
	int accepting_connection();
	void logMessage(const std::string& message);
};