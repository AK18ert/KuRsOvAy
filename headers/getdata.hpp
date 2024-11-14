
#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include "errorhandler.hpp"

using namespace std;
class getdata
{
private:
    string lp;
public:
    getdata(const string lpath);
    map<string, string> get(string fpath);
};
