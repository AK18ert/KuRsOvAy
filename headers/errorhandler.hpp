/** @file errorhandler.hpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Класс, обрабатывающий ошибки
 * @date 21.12.2023
 * @copyright ИБСТ ПГУ
 */
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <stdexcept>

/**
 * @brief Класс обработки ошибок записи в журнал
 */
class log_err: public std::runtime_error
{
public:
    log_err(const std::string& s) : std::runtime_error(s) {}
    log_err(const char * s) : std::runtime_error(s) {}
};

/**
 * @brief Класс обработки ошибок аутентификации
 */
class auth_err: public std::invalid_argument
{
public:
    auth_err(const std::string& s) : std::invalid_argument(s) {}
    auth_err(const char * s) : std::invalid_argument(s) {}
};

/**
 * @brief Класс обработки ошибок чтения
 */
class read_err: public std::invalid_argument
{
public:
    read_err(const std::string& s) : std::invalid_argument(s) {}
    read_err(const char * s) : std::invalid_argument(s) {}
};

/**
 * @brief Функция записи ошибок в журнал
 * @param lp Путь к файлу журнала
 * @param what Содержание ошибки
 * @return log_s Строка с логом ошибки
 */
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
        file.close();
		lp = "log.txt";
		std::ofstream file(lp.c_str(), std::ios::app);
		if (file.is_open()) {
			cout << "Путь /var/log/ccalc.log недоступен, использован лог-файл из локальной папки" << endl;
			std::time_t now = time(0);
			std::string date = std::ctime(&now);
			log_s = " - " + what + "\n";
			file << date+log_s;
			file.close();
		} else {
			file.close();
			throw log_err("Error opening log file");
		}
    }
    return log_s;
}