#ifndef FAKESERVER_H
#define FAKESERVER_H

#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <chrono>
#include "shared/Packet.hpp"

class FakeServer {
  public:
    typedef std::vector<std::string> Strings;
    typedef std::vector<std::fstream*> Files;

    // ile polaczen, jaki sufiks nazwy plikow, jakie wejscia
    FakeServer(int x, std::string channel_, Strings INS);
    ~FakeServer();
    bool scan_file(int x);
    void send(int x, Packet::StreamBuffer data);
    void run(); // zeby nie zawieszac programu, mozna odpalic w innym watku
    std::queue<Packet> to_send;
    std::queue<Packet> received;
    /*
     * ponizej sa handlery, podobne co beda w oryginalnym serwerze, jednak formalizm jest troche inny -
     * w oryginalnym serwerze beda watki znajace adres klienta, wiec te funkcje beda bez argumentow
     */
    // buduje pakiet i przenosi go na kolejke received
    void handleAccept(Packet::Address);
    // rejestruje polaczenie z klientem o okreslonym adresie
    void handleStart(Packet::Address);
    // wyrejestrowuje klienta z okreslonym adresem
    void handleFinish(Packet::Address);
  private:
    const std::chrono::milliseconds sleep_time_;
    bool running_;
    const int num_of_connections_;
    const std::string channel_;
    Strings out_names;
    Strings in_names;

    //to też wektory?
    Files ins;
    Files outs;
};

#endif // FAKESERVER_H
