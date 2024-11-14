
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
