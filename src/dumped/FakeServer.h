#ifndef FAKESERVER_H
#define FAKESERVER_H

#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <chrono>
#include "shared/Packet.hpp"
#include "shared/typedefinitions.hpp"
#include "server/ServerResources.hpp"

class SureOpen;

class FakeServer : public ServerResources {
  public:
    typedef std::vector<std::string> Strings;
    typedef std::vector<std::fstream *> Files;

    // ile polaczen, jaki sufiks nazwy plikow, jakie wejscia
    FakeServer(int connectionsNumber, std::string channelName, Strings inFilesNames);
    ~FakeServer();

    void scan_file(int x);
    void send(int x, Packet::StreamBuffer data);
    void run(); // zeby nie zawieszac programu, mozna odpalic w innym watku

    /*
     * ponizej sa handlery, podobne co beda w oryginalnym serwerze, jednak formalizm jest troche inny -
     * w oryginalnym serwerze beda watki znajace adres klienta, wiec te funkcje beda bez argumentow
     */
    // buduje pakiet i przenosi go na kolejke received
    void handle_accept(Address addr);
    // rejestruje polaczenie z klientem o okreslonym adresie
    void handle_start(Address);
    // wyrejestrowuje klienta z okreslonym adresem
    void handle_finish(Address);


  private:
    static const std::chrono::milliseconds sleepTime_;
    const int numberOfConnections_;
    const std::string channel_;
    Strings outNames_;
    Strings inNames_;


    Files ins;
    Files outs;

    friend class SureOpen;
};

#endif // FAKESERVER_H
