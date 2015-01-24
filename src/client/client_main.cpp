/******************************************************
Prosty klient.
Program:
1. łączy się z serwerem o zadanym ip i porcie
2. wysyła do niego to, co jest przekazane w standardowym strumieniu cin
3. odbiera odpowiedzi od serwera i wypisuje je na cout

Kompilacja z użyciem g++:
g++ -o cli -std=c++11 -Wall main.cpp -lboost_system

Użycie:
./cli <ip w postaci xxx.xxx.xxx.xxx (ipv6 też pewnie zadziała)> <numer portu(liczba)>

******************************************************/

#include <iostream>
#include <boost/asio.hpp>
#include "shared/Packet.hpp"
#include "shared/ChatEntryRaw.hpp"
#include "shared/GameRoomRaw.hpp"
#include "shared/HandshakeRaw.hpp"
#include "shared/typedefinitions.hpp"
#include "server/ClientDataRaw.hpp"
#include "server/PacketQueueAdapter.hpp"

BOOST_CLASS_EXPORT(ChatEntryRaw)
PacketQueue  p;

using namespace boost::asio;

std::size_t completion(const boost::system::error_code &error, std::size_t /*bytes_transferred*/) {
    return ! error;
}

void writeHandler(const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/) {
    std::cout << "***Hello! Write handler here!***\n";
}

void readHandler(const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/) {
    std::cout << "***Hello! Read handler here!***\n";
}

int main(int argc, char *argv[]) {

    std::string txData;
    std::getline(std::cin, txData);     //wczytywanie danych ze standardowego wejścia


    if(argc != 3) {
        std::cout << "usage: ip port \n";
        return 1;


    }

    std::string addrStr(argv[1]);
    short port = atoi(argv[2]);

    io_service io;

    ip::address address = ip::address::from_string(addrStr);
    ip::tcp::endpoint endpoint(address, port);
    ip::tcp::socket socket(io);
    socket.connect(endpoint);

    streambuf transmission;
    std::ostream transmissionStream(&transmission);
    transmissionStream << txData;

    async_write(socket, transmission, transfer_all(), writeHandler);        //asynchroniczne wysyłanie danych do serwera

    streambuf response;
    boost::system::error_code ec;
    async_read(socket, response, transfer_all(), readHandler);
    io.run();
    std::cout << "Server's response: " << &response << std::endl;

    return 0;
}
