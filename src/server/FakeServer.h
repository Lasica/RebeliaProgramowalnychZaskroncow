#ifndef FAKESERVER_H
#define FAKESERVER_H

#include <fstream>
#include <sstream>
#include <queue>
#include "shared/Packet.hpp"

class FakeServer
{
public:
    // ile polaczen, jaki sufiks nazwy plikow, jakie wejscia
    FakeServer(int x, std::string channel_, std::string INS[num_of_connections] );
    bool scan_file(int x);
    void send(int x, std::stingstream data);
    void run(); // zeby nie zawieszac programu, mozna odpalic w innym watku
    std::queue<Packet> to_send;
private:
    bool running;
    const std::string channel;
    const int num_of_connections;
    std::string out_names[num_of_connections];
    std::string in_names[num_of_connections];
    std::fstream ins[num_of_connections];
    std::fstream outs[num_of_connections];
};

#endif // FAKESERVER_H
