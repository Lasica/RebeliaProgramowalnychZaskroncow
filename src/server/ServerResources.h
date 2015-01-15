#ifndef SERVERRESOURCES_H
#define SERVERRESOURCES_H

#include <chrono>
#include "server/ClientsRegister.hpp"
#include "shared/typedefinitions.h"
#include "server/Packet_handler.h"

struct ServerResources {
    std::thread packetHandler;
    PacketQueue received;
    PacketQueue toSend;

    Packet_handler lobbyManager;
    ClientsRegister connectedClients;

    ServerResources() : lobbyManager(&received, &running_, std::chrono::milliseconds(10)) { // TODO 10 magical number
    }

    void init() {
        running_ = true;
        packetHandler = std::thread(lobbyManager);
    }
    virtual ~ServerResources() {
        running_ = false;
        packetHandler.join();
    }

  protected:
    bool running_;
};

#endif // SERVERRESOURCES_H
