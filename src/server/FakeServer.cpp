#include "FakeServer.h"
#include "shared/Packet.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

const std::chrono::milliseconds FakeServer::sleep_time_(500);

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
            std::this_thread::sleep_for(FakeServer::sleep_time_);
        }
    }
    ~SureOpen() {
        ptr->close();
    }
};



FakeServer::FakeServer(int x, std::string channel_, Strings INS) :
    num_of_connections_(x), channel_(channel_), in_names(INS)  {
    out_names.resize(num_of_connections_);
    in_names.resize(num_of_connections_);

    for(int i = 0; i < num_of_connections_; ++i) {
        ins.push_back(new std::fstream);
        outs.push_back(new std::fstream);

        out_names[i] = (std::to_string(i) + std::string("_") + channel_);

        send(i, std::string("hello"));
    }
}

FakeServer::~FakeServer() {
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
            scan_file(i);

        // sprawdz kolejke wysylkowa
        if(!to_send.empty()) {
            std::cout << "Dane do wyslania: " << to_send.size() << std::endl;

            Packet a = to_send.front();
            to_send.pop();
            int address = a.get_address();
            Packet::StreamBuffer data = a.get_data_streambuf();

            send(address, data);
        }

        //TODO: running_ = liczba_klientow > 0;
        std::this_thread::sleep_for(sleep_time_);
    }
}


void FakeServer::scan_file(int x) {
    try {
        std::string line;
        std::string receivedData;   //czyścić to przed wejściem do kolejnego pliku?
        {
            SureOpen file(ins[x], in_names[x], std::fstream::in);


            while ( getline (*ins[x], line) ) {
                std::cout << "Wczytalem linie z kanalu " << x << ":\n" << line << '\n'; //DEBUG

                if(line == "hello") {  // "hello" <=> nowy Client prosi o zarejestrowanie
                    Address incomingConnectionAddress;
                    incomingConnectionAddress.ip = x;
                    incomingConnectionAddress.port = x;
                    incomingConnectionAddress.nickname = in_names[x];

                    handleStart(incomingConnectionAddress);       // rejestracja nowego klienta

                }
                else if(line == "bye") {    // "bye" <=> istniejący Client prosi o wyrejestrowanie
                    Address disconnectAddress;
                    disconnectAddress.ip = x;
                    disconnectAddress.port = x;
                    disconnectAddress.nickname = in_names[x];
                    handleFinish(disconnectAddress);                // wyrejestruj klienta pod adresem x
                } else
                    receivedData += line;
            }
        }

        if(receivedData.length()) {

            Packet newP;
            std::stringstream ifs;          //na razie, żeby sprawdzić, czy wczytywanie i deserializacja zadzialają
            boost::archive::text_iarchive ia(ifs);
            ia >> newP;
            received.push(newP);

            std::cout << received.back().Packet::get_data_string(); // pokzuje na cout zawartość odebranego pakietu (tylko dla testów)
        }
    } // koniec bloku SureOpen - zamkniecie pliku
catch(...) {
    std::cout << "wyjatek!!! Nieprawidlowe dane sterujace (pakiet)\n";    // tymczasowo, dla (nie)bezpieczenstwa
}

{
    // wyczysc zawartosc wczytana z pliku
    SureOpen(ins[x], in_names[x], std::fstream::out | std::fstream::trunc);
}
}

void FakeServer::send(int x, Packet::StreamBuffer data) {
    std::cout << "Wysylam dane na kanal " << x << ":\n" << data << std::endl;
    SureOpen file(outs[x], out_names[x], std::fstream::out | std::fstream::trunc);
    *outs[x] << data;
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
