#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "server/Server.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
BOOST_CLASS_EXPORT(ChatEntryRaw)

//#include "Logger.hpp"
using boost::asio::ip::tcp;
using namespace boost::asio;
int main() {
    TcpServer &server = TcpServer::getInstance();
    server.start();

    std::cout << "Serwer uruchomiony\n";

    char input = -1;

    do {
        std::cin >> input;

    } while(input != 'q');
    TcpServer::getInstance().stop();

    return 0;
}
