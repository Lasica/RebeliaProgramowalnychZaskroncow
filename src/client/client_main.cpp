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

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/queue.hpp>
#include <boost/serialization/serialization.hpp>
#include "shared/Packet.hpp"
#include "shared/ChatEntryRaw.hpp"
#include "shared/GameRoomRaw.hpp"
#include "shared/HandshakeRaw.hpp"
#include "shared/typedefinitions.hpp"
#include "server/ClientDataRaw.hpp"
#include "server/PacketQueueAdapter.hpp"
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>

std::queue<Packet> to_send;
std::queue<Packet> received;

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
    if(argc != 5) {
        std::cout << "usage: ip, port, nickname, input_file\n";
        return 1;
    }

    std::string addrStr(argv[1]);
    short port = atoi(argv[2]);
    /*try {
        std::ifstream ifs(argv[3]);
        boost::archive::text_iarchive ia(ifs);
        ia & to_send;
        ifs.close();
    } catch(std::exception &e) {
        cout << e.what() << endl;
    }*/
    Packet p1(Packet::REGISTER_REQUEST, nullptr, new  HandshakeRaw(argv[3]));
    Packet p2(Packet::KEEP_ALIVE);
    to_send.push(p1);
    to_send.push(p2);
    std::cout << to_send.front().get_content()->show_content() << std::endl;
    std::cout << to_send.front().get_data_streambuf() << std::endl;
    std::cout << to_send.front().get_tag() << " TAG " << Packet::REGISTER_REQUEST << " " << Packet::KEEP_ALIVE << std::endl;
    io_service io;
    auto thr = new std::thread(boost::bind(&boost::asio::io_service::run, &io));

    ip::address address = ip::address::from_string(addrStr);
    ip::tcp::endpoint endpoint(address, port);
    ip::tcp::socket socket(io);
    socket.connect(endpoint);

    std::chrono::milliseconds sleeptime(500);
    int ctr=0;
    boost::asio::streambuf rb;
    boost::asio::streambuf wb;
    while(!to_send.empty()) {
        if(to_send.front().get_tag() == Packet::KEEP_ALIVE and ctr < 10) {
            /*std::ostream sending(&wb);
            std::cout << "sending" << to_send.front().get_data_streambuf() << std::endl;
            sending << to_send.front().get_data_streambuf();
            async_write(socket, wb, transfer_all(), writeHandler);*/
            ++ctr;
            std::cout << "Waiting... " << ctr << std::endl;
            std::this_thread::sleep_for(sleeptime);
        } else if (to_send.front().get_tag() == Packet::KEEP_ALIVE) {
            ctr = 0;
            to_send.pop();
        } else {
            std::ostream sending(&wb);
            std::cout << "sending" << to_send.front().get_data_streambuf() << std::endl;
            sending << to_send.front().get_data_streambuf();
            async_write(socket, wb, transfer_all(), writeHandler);
            to_send.pop();
        }


        std::istream ib(&rb);
        async_read(socket, rb, transfer_all(), readHandler);
        if(!ib) {
            std::cout << ib << std::endl;
        }
    }
    //async_write(socket, transmission, transfer_all(), writeHandler);        //asynchroniczne wysyłanie danych do serwera
    //boost::system::error_code ec;
    std::cout << "Bye!\n";
    io.stop();
    thr->join();
    return 0;
}
