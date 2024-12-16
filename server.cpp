/** @file server.cpp
 * @author Кочегаров А. И.
 * @version 1.0
 * @brief Функция запуска сервера, аутентификации, приема и обработки данных, записи логов
 * @date 15.12.2024
 * @copyright ИБСТ ПГУ
 */

#include "headers/server.hpp"
#include "headers/errorhandler.hpp"
#include "headers/getdata.hpp"
#include "headers/sha1hash.hpp"

using namespace std;

server::server(string fpath, int port, string lpath)
{
    lp = lpath;
    userdata = getdata(lp).get(fpath);
	port = port;
	address = "127.0.0.1";
    sckt = start();
}

int server::start()
{
	sockaddr_in* selfAddr = new (sockaddr_in);
    selfAddr->sin_family = AF_INET;
    selfAddr->sin_port = htons(port);
    selfAddr->sin_addr.s_addr = inet_addr(address);
    int s = socket(AF_INET, SOCK_STREAM, 0);
    int rc = bind(s, (const sockaddr*)selfAddr, sizeof(sockaddr_in));
	if (rc==-1){
		throw std::system_error(errno, std::generic_category(), "Ошибка создания сокета");
	}
	rc = listen(s, 5);
    if(rc == -1) {
        throw std::system_error(errno, std::generic_category(), "Ошибка при прослушивании сокета");
    }
    cout << "The server start" << endl;
	return s;

}

void server::logMessage(const string& message) {
    ofstream logFile("server.log", ios::app); 
    if (logFile.is_open()) {
        auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
        logFile << put_time(localtime(&now), "%Y-%m-%d %H:%M:%S") << " - " << message << endl;
        logFile.close();
    } else {
        cerr << "Не удалось открыть файл для записи логов." << endl;
    }
}


bool server::authentication()
{
    sha1h crypt;
    string err = "ERR";
    string ok = "OK";
    rc = recv(wrkr, buf, sizeof(buf), 0);
    buf[rc] = '\0';
    string ID(buf);
    if (userdata.count(ID) == 1) {
        strcpy(buf, crypt.salt.c_str());
        send(wrkr, buf, crypt.salt.length(), 0);
    } else {
        strcpy(buf, err.c_str());
        send(wrkr, buf, sizeof(buf), 0);
        close(wrkr);
        throw auth_err("Invalid client id");
        return false;
    }
    cout << "The client has been identified" << endl;
    rc = recv(wrkr, buf, 4096, 0);
    buf[rc] = '\0';
    string message(buf);
    if (message != crypt.hash(userdata[ID])) {
        strcpy(buf, err.c_str());
        send(wrkr, buf, err.length(), 0);
        close(wrkr);
        throw auth_err("Invalid password");
        return false;
    }
    strcpy(buf, ok.c_str());
    rc = send(wrkr, buf, ok.length(), 0);
    buf[rc] = '\0';
    cout << "The client has been authenticated" << endl;
    return true;
}
bool server::handling()
{
    uint32_t vectors_quantity;
    uint32_t vector_size;
    uint64_t vector;
    recv(wrkr, &vectors_quantity, sizeof(vectors_quantity), 0);
    for (uint32_t i = 0; i < vectors_quantity; i++) {
        int64_t proiz = 1;
        recv(wrkr, &vector_size, sizeof(vector_size), 0);
        for (uint32_t j = 0; j < vector_size; j++) {
            recv(wrkr, &vector, sizeof(vector), 0);
            proiz = proiz*vector;
        }
        uint64_t answer;

        answer = proiz;
		proiz = 1;
        send(wrkr, &answer, sizeof(answer), 0);
    }
    return true;
};

int server::accepting_connection()
{
    sockaddr_in* remoteAddr = new (sockaddr_in);
    remoteAddr->sin_family = AF_INET;
    remoteAddr->sin_port = 0;
    remoteAddr->sin_addr.s_addr = 0;
    sockaddr_in * client_addr = new sockaddr_in;
    socklen_t len = sizeof(sockaddr_in);
    wrkr = accept(sckt, (sockaddr*)(client_addr), &len);
    cout << "The server accepted the connection" << endl;
    return wrkr;
}