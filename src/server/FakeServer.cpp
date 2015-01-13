#include "FakeServer.h"
#include "shared/Packet.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

const std::chrono::milliseconds FakeServer::sleepTime_(500);

/*
 * Pomocnicza klasa do tworzenia obiektow automatycznych dbajaca o otwarcie i zamkniecie pliku w zakresie nazw
 */
class SureOpen {
    std::fstream *ptr;
  public:
    SureOpen(std::fstream *ptr_, std::string &name, std::ios_base::openmode mode) : ptr(ptr_) {
        while(true) {
            ptr->open(name, mode);

            if(ptr->is_open()) // upewnij sie, ze udalo sie otworzyc plik
                break;

            std::cout << "Nieudana proba otwarcia pliku " << name << std::endl;
            std::this_thread::sleep_for(FakeServer::sleepTime_);
        }
    }
    ~SureOpen() {
        ptr->close();
    }
};



FakeServer::FakeServer(int x, std::string channel_, Strings INS) :
    ServerResources(), numberOfConnections_(x), channel_(channel_), inNames_(INS)  {
    outNames_.resize(numberOfConnections_);
    inNames_.resize(numberOfConnections_);

    for(int i = 0; i < numberOfConnections_; ++i) {
        ins.push_back(new std::fstream);
        outs.push_back(new std::fstream);

        outNames_[i] = (std::to_string(i) + std::string("_") + channel_);

        send(i, std::string("hello"));
    }
}

FakeServer::~FakeServer() {
    for(int i = 0; i < numberOfConnections_; ++i) {
        delete ins[i];
        delete outs[i];
    }
}



void FakeServer::run() { // do odpalenia w innym watku?
    // dodac watki do odpalenia
    ServerResources::init();
    int iterations = 0;

    while(running_) {
        std::cout << "Iteracja... " << iterations++ << std::endl;

        // sprawdz kanaly przychodzace
        for(int i = 0; i < numberOfConnections_; ++i)
            scan_file(i);

        // sprawdz kolejke wysylkowa
        if(!toSend.empty()) {
            std::cout << "Dane do wyslania: " << toSend.size() << std::endl;

            Packet a = toSend.front();
            toSend.pop();
            int address = a.get_address();
            Packet::StreamBuffer data = a.get_data_streambuf();

            send(address, data);
        }

        // DEBUG
        std::cout << "Received packets so far: " << received.size() << std::endl;


        //TODO: running_ = liczba_klientow > 0;
        std::this_thread::sleep_for(sleepTime_);
    }

}


void FakeServer::scan_file(int x) {
    try {
        std::string line;
        std::string receivedData;
        {
            SureOpen file(ins[x], inNames_[x], std::fstream::in);


            while ( getline (*ins[x], line) ) {
                std::cout << "Wczytalem linie z kanalu " << x << ":\n" << line << '\n'; //DEBUG

                if(line == "hello") {  // "hello" <=> nowy Client prosi o zarejestrowanie
                    Address incomingConnectionAddress;
                    incomingConnectionAddress.ip = x;
                    incomingConnectionAddress.port = x;
                    incomingConnectionAddress.nickname = inNames_[x];

                    handle_start(incomingConnectionAddress);       // rejestracja nowego klienta

                } else if(line == "bye") {  // "bye" <=> istniejący Client prosi o wyrejestrowanie
                    Address disconnectAddress;
                    disconnectAddress.ip = x;
                    disconnectAddress.port = x;
                    disconnectAddress.nickname = inNames_[x];
                    handle_finish(disconnectAddress);                // wyrejestruj klienta pod adresem x
                } else {
                    receivedData += line;
                    std::cout << "*** Received data:\n";
                    std::cout << receivedData << std::endl;
                }
            }
        }

        if(receivedData.length()) {

            Packet newP;
            std::stringstream ifs;          //na razie, żeby sprawdzić, czy wczytywanie i deserializacja zadzialają
            ifs << receivedData;
            boost::archive::text_iarchive ia(ifs);
            ia >> newP;
            received.push(newP);

        }
    } // koniec bloku SureOpen - zamkniecie pliku
    catch(std::exception &e) {
        std::cerr << "Wyjatek!!! Nieprawidlowe dane (pakiet)\n" << e.what() << std::endl;    // tymczasowo, dla (nie)bezpieczenstwa
    }

    {
        // wyczysc zawartosc wczytana z pliku
        SureOpen(ins[x], inNames_[x], std::fstream::out | std::fstream::trunc);
    }
}

void FakeServer::send(int x, Packet::StreamBuffer data) {
    std::cout << "Wysylam dane na kanal " << x << ":\n" << data << std::endl;
    SureOpen file(outs[x], outNames_[x], std::fstream::out | std::fstream::trunc);
    *outs[x] << data;
}



void FakeServer::handle_accept(Address addr) {
    ;
}

void FakeServer::handle_finish(Address addr) {
    connectedClients.remove_client(connectedClients.look_up_with_address(addr));


    // do testów
    std::cout << "Wyrejestrowuje klienta o adresie " << addr << ". Zostalo " << connectedClients.get_size() << " klientow.\n";
}

void FakeServer::handle_start(Address addr) {
    connectedClients.register_client(addr.nickname, 5, 7, IN_LOBBY, "");

    // do testów
    std::cout << "Rejestruje klienta o adresie" << addr << ". Jest obecnie " << connectedClients.get_size() << " klientow.\n";
}
