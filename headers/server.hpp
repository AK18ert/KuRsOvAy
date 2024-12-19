/** @file server.hpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Класс, управляющий работой сервера
 * @date 15.12.2024
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
    ///Порт подключения
	int port;
    ///Адрес подключения
	const char* address;
	///Путь к файлу с логом
	std::string lp;
    ///Сокет
	int sckt;
    ///Действующее соединение с клиентом
    int wrkr;
	///Ответ от клиента
    int rc;
	///Буфер
    char *buf = new char[4096];
	///Данные клиента ID:PASS
    std::map <std::string, std::string> userdata;
    /**
     * @brief Функция запуска сервера и привязки порта
     * @param port Порт для приема соединения (Задается в server и берется уже из привата)
     * @param address Сетевой адрес для приема соединения (Задается в server и берется уже из привата)
     * @return sckt Сокет (Создается уже в функции)
     */
	int start();

public:
    /**
     * @brief Конструктор класса
     * @param fpath Путь к файлу с ID:PASS клиентов
     * @param port Порт для приема соединения
     * @param lpath Путь к файлу журнала
     */
    server(std::string fpath, int port, std::string lpath);
	/**
     * @brief Функция аутентификации пользователя
     * @return True, если аутентификация удалась, False - если нет
     */
    bool authentication();
    /**
     * @brief Функция обработки векторов
     * @return True, если обработка удалась, False - если нет
     */
	bool handling();
	/**
     * @brief Функция ожидания и принятия соединения с клиентом
     * @return wrkr Действующее соединение с клиентом
     */
	int accepting_connection();

};