/** @file main.cpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Функция вывода справки и точка входа в программу
 * @date 15.12.2024
 * @copyright ИБСТ ПГУ
 */
#include <iostream>
#include <string>
#include "headers/server.hpp"
#include "headers/getdata.hpp"
#include <cryptopp/hex.h>
#include "headers/sha1hash.hpp"
#include <string.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

struct {
    uint32_t p=33333;
    std::string f="database.txt";
    std::string l="log.txt";
    bool p_not_set()
    {
        return(p==33333);
    }
    bool b_not_set()
    {
        return(f=="database.txt");
    }
    bool l_not_set()
    {
        return(l=="log.txt");
    }
} params;

void help()
{
    std::cout << "enter -h / --help for help;\nenter -f / --database-path for the path to the database with clients;\nenter -l / --log-path for the path to the log file;\nenter -p / --port for the port\n";
}

int main(int argc, const char* argv[])
{

    std::string fpath;
    int port;
    std::string lpath;
    try {
        po::options_description desc("Allowed options");
        desc.add_options()
        ("help,h", "produce help message")
        ("database-path,f", po::value<std::string>(&fpath)->default_value("/etc/vcalc.conf"), "path to the database with clients")
        ("log-path,l", po::value<std::string>(&lpath)->default_value("/var/log/ccalc.log"), "path to the log file")
        ("port,p", po::value<int>(&port)->default_value(33333), "port");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            help();
            return 1;
        }
        params.f = fpath;
        params.p = port;
        params.l = lpath;
        if (params.p_not_set() && params.b_not_set() && params.l_not_set()) {
            help();
        }
        server srvr = server(fpath, port, lpath);
        while (true) {
            srvr.accepting_connection();
            if (srvr.authentication() == true)
                srvr.handling();
        }
    } catch(log_err &e) {
		help();
        std::cerr << e.what() << std::endl;
    } catch(std::exception &e) {
		help();
        std::cerr << e.what() << std::endl;
        logger(lpath, e.what());
    }
    return 0;
}
