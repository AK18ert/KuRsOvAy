#include <iostream>
#include <string>
#include "headers/server.hpp"
#include "headers/getdata.hpp"
#include <cryptopp/hex.h>
#include "headers/sha1hash.hpp"
#include <string.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
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
        ("database-path,f", po::value<std::string>(&fpath)->default_value("database.txt"), "path to the database with clients")
        ("log-path,l", po::value<std::string>(&lpath)->default_value("log.txt"), "path to the log file")
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
        std::cerr << e.what() << std::endl;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
        logger(lpath, e.what());
    }
    return 0;
}
