#include "FakeServer.h"
#include "shared/Packet.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>



FakeServer::FakeServer(int x, std::string channel_, Strings INS) :
    sleep_time_(500), num_of_connections_(x), channel_(channel_), in_names(INS)  {
    out_names.resize(num_of_connections_);
    in_names.resize(num_of_connections_);

    for(int i = 0; i < num_of_connections_; ++i) {
        ins.push_back(new std::fstream);
        outs.push_back(new std::fstream);
        out_names[i] = (std::to_string(i) + std::string("_") + channel_);
        send(i, std::string("hello"));
    }
}

FakeServer::~FakeServer() {             // zastąpić clearem? vector sam się nie wyczyści przy dekonstruowaniu?
    for(int i = 0; i < num_of_connections_; ++i) {
        delete ins[i];
        delete outs[i];
    }
}



void FakeServer::run() { // do odpalenia w innym watku?
    // dodac watki do odpalenia
    running_ = true;
    int iterations = 0;

    while(running_) {
        std::cout << "Iteracja... " << iterations++ << std::endl;

        // sprawdz kanaly przychodzace
        for(int i = 0; i < num_of_connections_; ++i)
            running_ = scan_file(i);

        // sprawdz kolejke wysylkowa
        if(!to_send.empty()) {
            std::cout << "Dane do wyslania: " << to_send.size() << std::endl;
            Packet a = to_send.front();
            to_send.pop();
            int address = a.get_address();
            Packet::StreamBuffer data = a.get_data_streambuf();  // # buf zamiast buff
            send(address, data);
        }

        std::this_thread::sleep_for(sleep_time_);
    }
}

bool FakeServer::scan_file(int x) {
    bool ret = true;

    try {
        std::string line;
        std::string receivedData;   //czyścić to przed wejściem do kolejnego pliku?
        bool message = false;

        while(true) {
            ins[x]->open(out_names[x], std::fstream::in);

            if(ins[x]->is_open())
                break;

            if(!message) {
                std::cout << "Nieudana proba otwarcia pliku w celu odczytu " << in_names[x] << std::endl;
                std::this_thread::sleep_for(4 * sleep_time_);
                //message = true;
            }
        }

        // wczytaj i handluj jako pakiet, jesli bylo exit - to exit. TODO
        while ( getline (*ins[x], line) ) {
            std::cout << line << '\n';

            if(line == "hello") {
                Address incomingConnectionAddress;
                incomingConnectionAddress.ip = x;
                incomingConnectionAddress.port = x;
                incomingConnectionAddress.nickname = in_names[x];

                handleStart(incomingConnectionAddress);                 // typ x - musi być zamieniony na Address

            } // start connection
            else if(line == "bye") {
                Address disconnectAddress;
                disconnectAddress.ip = x;
                disconnectAddress.port = x;
                disconnectAddress.nickname = in_names[x];

                handleFinish(disconnectAddress);

                handleFinish(disconnectAddress);
                ret = false; // quit connection
            } else {
                receivedData += line;   //trzeba zaznaczyć, że to dzieje się jeśli było poprzedzone "hello"
            }

            //set running false if there are no connections
        }

        if(!receivedData.length()) {

            Packet newP;
            //std::ifstream ifs("filename");
            std::stringstream ifs;          //na razie, żeby sprawdzić, czy wczytywanie i deserializacja zadzialają
            boost::archive::text_iarchive ia(ifs);
            ia >> newP;

            received.push(newP);

            std::cout << received.back().get_data_string(); // pokzuje na cout zawartość odebranego pakietu (tylko dla testów)
        }




        ins[x]->close();
    } catch(...) {
    }

    return ret;
}

void FakeServer::send(int x, Packet::StreamBuffer data) {
    bool message = false;

    while(true) {
        outs[x]->open(in_names[x], std::fstream::out | std::fstream::trunc);

        if(outs[x]->is_open())
            break;

        if(!message) {
            std::cout << "Nieudana proba otwarcia pliku w celu zapisu " << out_names[x] << std::endl;
            //message = true;
            std::this_thread::sleep_for(sleep_time_);
        }
    }

    *outs[x] << data;
    outs[x]->close();
}

void FakeServer::handleAccept(Address addr) {
    ;
}

void FakeServer::handleFinish(Address addr) {
    connectedClients.remove_client(connectedClients.look_up_with_address(addr));


    // do testów
    std::cout << "*** Hello FakeServer::handleFinish here! ***" << std::endl;
}

void FakeServer::handleStart(Address addr) {
    connectedClients.register_client(addr.nickname, 5, "111.111.111.111", IN_LOBBY, "");

    // do testów
    std::cout << "*** Hello FakeServer::handleStart here! ***" << std::endl;
}
