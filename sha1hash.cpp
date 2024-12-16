/** @file sha1hash.cpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Функция хэширования и генерации соли
 * @date 15.12.2024
 * @copyright ИБСТ ПГУ
 */
#include "headers/sha1hash.hpp"
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <unistd.h> 
#include <ctime> 
using namespace std;

sha1h::sha1h(){
	salt = salt_generator();
	}
	
string sha1h::hash(const string password){
	using namespace CryptoPP;
    SHA1 hash;
    std::string msg = salt + password;
    std::string digest;
    StringSource(msg, true,           
                 new HashFilter(hash,      
                                new HexEncoder(     
                                    new StringSink(digest))));
    return digest;
}
string sha1h::salt_generator(){
	srand(time(NULL));
	static const char alphanum[] =
        "0123456789"
        "ABCDEF";
    string tmp_s;
    tmp_s.reserve(16);
    for (int i = 0; i < 16; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    return tmp_s;
}
