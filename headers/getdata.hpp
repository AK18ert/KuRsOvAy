/** @file getdata.hpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Класс, читающий базу данных
 * @date 21.12.2023
 * @copyright ИБСТ ПГУ
 */
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
