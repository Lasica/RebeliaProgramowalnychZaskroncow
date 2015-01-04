#ifndef FAKESERVER_H
#define FAKESERVER_H

#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include "shared/Packet.hpp"

class FakeServer {
  public:
    typedef std::vector<std::string> Strings;
    typedef std::vector<std::fstream> Files;

    // ile polaczen, jaki sufiks nazwy plikow, jakie wejscia
    FakeServer(int x, std::string channel_, Strings INS);
    bool scan_file(int x);
    void send(int x, Packet::StreamBuffer data);
    void run(); // zeby nie zawieszac programu, mozna odpalic w innym watku
    std::queue<Packet> to_send;
  private:
    bool running;
    const int num_of_connections;
    const std::string channel;
    Strings out_names;
    Strings in_names;

    //to też wektory?
    Files ins;
    Files outs;
};

#endif // FAKESERVER_H
