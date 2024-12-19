/** @file getdata.cpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Функция чтения базы данных
 * @date 15.12.2024
 * @copyright ИБСТ ПГУ
 */
#include "headers/getdata.hpp"
using namespace std;
getdata::getdata(const string fpath)
{
    fp = fpath;
}
map <string, string> getdata::get()
{
    map <string, string> userdata;
    string line;
    ifstream in(fp);
    if (in.is_open()) {
        while (getline(in, line)) {
            int position = line.find(':');
            string ID;
            string password;
            for (int n = 0; n < position; n++)
                ID += line[n];
            for (uint n = position+1; n < line.length(); n++)
                password += line[n];
            userdata[ID] = password;
        }
    } else
        throw read_err("Failed to open database");
    in.close();
    return userdata;
}
