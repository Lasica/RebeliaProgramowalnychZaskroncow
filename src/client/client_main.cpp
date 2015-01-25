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
#include <assert.h>
std::queue<Packet> to_send;
std::queue<Packet> received;

using namespace boost::asio;
io_service io;
ip::tcp::socket sckt(io);

boost::asio::streambuf rb;

std::size_t completion(const boost::system::error_code &error, std::size_t /*bytes_transferred*/) {
    return ! error;
}

void writeHandler(const boost::system::error_code & /*error*/, std::size_t /*s*/) {
    std::cout << "***Hello! Write handler here!***\n";
}

//void readHandler(const boost::system::error_code &/*error*/, std::size_t bytes_transferred) {
//    std::cout << "***Hello! Read handler here!***\n";
//     if(size > 1) {
//         std::cout << "READ_HANDLER with size = " << size << " / " << response_.size() << std::endl;
//         std::iostream is(&response_);
//         try {
//             char * rd=nullptr;
//             is.get(rd, size, '\r');
//             std::string str(rd);
//             std::stringstream IS(str);
//             //while (std::getline(is, str)) { std::cout << str << std::endl; }
//             Packet packet(Packet::Packet::KEEP_ALIVE, TcpServer::getInstance().registeredAddresses.get_address_pointer(Address(ip_address(), port())), nullptr);
//             boost::archive::text_iarchive ia(IS);
//                 ia >> packet;
//
//             std::cout << "Received packet with tag: " << packet.get_tag() << std::endl;
//             if(packet.get_content() != nullptr) {
//                 std::cout << "Content: " << packet.get_content()->show_content() << std::endl;
//             }
// //             response_.consume(size);
//             TcpServer::getInstance().received.push(packet);
//             //response_.consume(1000);
//             while (std::getline(is, str)) { /*std::cout << str << std::endl;*/ }
//         }
//         catch(std::exception ex) {
//             std::cerr << "Błąd serializacji pakietu " << ex.what() << std::endl;
//             std::iostream is(&response_);
//             std::string str;
//             while (std::getline(is, str)) { std::cout << str << std::endl; }
//             //response_.consume(1000);
//         }
//     } else if(size > 0) {
//         std::cout << "READ_HANDLER with size = " << size << " / " << response_.size() << " Consuming them." << std::endl;
//         response_.consume(size);
//     }
//     wait_data();
//}

void readHandler(const boost::system::error_code &/*error*/, std::size_t size) {
    if(size > 1) {
        std::cout << "READ_HANDLER with size = " << size << " / " << rb.size() << std::endl;
        std::iostream is(&rb);
        try {
            char buffer[1000];
            is.get(buffer, size, '\r');
            std::string str(buffer);
            std::stringstream IS(str);

            Packet packet(Packet::Packet::KEEP_ALIVE, nullptr, nullptr);

            boost::archive::text_iarchive ia(IS);
                ia >> packet;

            std::cout << "Received packet with tag: " << packet.get_tag() << std::endl;
            if(packet.get_content() != nullptr) {
                std::cout << "Content: " << packet.get_content()->show_content() << std::endl;
            }

//            TcpServer::getInstance().received.push(packet);
            while (std::getline(is, str)) { /*std::cout << str << std::endl;*/ }
        }
        catch(std::exception ex) {
            std::cerr << "Błąd serializacji pakietu " << ex.what() << std::endl;
            std::string str;
            while (std::getline(is, str)) { std::cout << str << std::endl; }
        }
    } /* else if(size > 0) {
        std::cout << "READ_HANDLER with size = " << size << " / " << response_.size() << " Consuming them." << std::endl;
        response_.consume(size);
    }*/
    //wait_data();

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
    Packet p3(Packet::LOG_OUT_REQUEST);
    to_send.push(p1);
    to_send.push(p2);
    to_send.push(p3);
    //io_service io;

    ip::address address = ip::address::from_string(addrStr);
    ip::tcp::endpoint endpoint(address, port);
    ip::tcp::socket sckt(io);
    sckt.connect(endpoint);
    auto thr = new std::thread(boost::bind(&boost::asio::io_service::run, &io));


    //boost::asio::streambuf rb;
        async_read_until(sckt, rb, "\r",  readHandler);


    std::chrono::milliseconds sleeptime(2000);
    int ctr=0;

    boost::asio::streambuf wb;
    while(!to_send.empty()) {
        if(to_send.front().get_tag() == Packet::KEEP_ALIVE and ctr < 3) {
            std::ostream sending(&wb);
            std::cout << "sending" << to_send.front().get_data_streambuf() << std::endl;
            sending << to_send.front().get_data_streambuf() << "\r";//<< EOF;
            async_write(sckt, wb, writeHandler);
            ++ctr;
            std::cout << "Waiting... " << ctr << std::endl;
            std::this_thread::sleep_for(sleeptime);
        } else if (to_send.front().get_tag() == Packet::KEEP_ALIVE) {
            ctr = 0;
            to_send.pop();
        } else {
            std::ostream sending(&wb);
            std::cout << "sending" << to_send.front().get_data_streambuf() << std::endl;
            sending << to_send.front().get_data_streambuf() << "\r";// << EOF;
            async_write(sckt, wb, writeHandler);
            to_send.pop();
        }
            std::istream is(&wb);
            std::string str;
            while (std::getline(is, str)) { /*std::cout << str << std::endl;*/ }
    }

    std::cout << &rb << std::endl;
    std::cout << "Bye!\n";
    io.stop();
    thr->join();
    return 0;
}
