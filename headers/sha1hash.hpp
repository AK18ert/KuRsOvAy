/** @file sha1hash.hpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Класс, отвечающий за хэширование и генерацию соли
 * @date 21.12.2023
 * @copyright ИБСТ ПГУ
 */
#pragma once
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>

using namespace std;

class sha1h
{
private:

	string salt_generator();
public:

	sha1h();
	string salt;

	string hash(const string password);
};
