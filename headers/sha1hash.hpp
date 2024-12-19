/** @file sha1hash.hpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Класс, отвечающий за хэширование и генерацию соли
 * @date 15.12.2024
 * @copyright ИБСТ ПГУ
 */
#pragma once
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

/**
 * @brief Класс, отвечающий за хэширование и генерацию соли
 */

using namespace std;

class sha1h
{
private:
	/**
	 * @brief Генератор соли
	 * @return string Соль
	 */
	string salt_generator();
public:
	/**
	 * @brief Конструктор класса
	 */
	sha1h();
	///Соль
	string salt;
	/**
	 * @brief Получение хэша от пароля
	 * @param password Пароль
	 * @return string Хэш от пароля
	 */
	 string hash(const string password);
};
