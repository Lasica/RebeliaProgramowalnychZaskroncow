#ifndef SERVERRESOURCES_H
#define SERVERRESOURCES_H

#include <chrono>
#include "server/ClientsRegister.hpp"
#include "shared/typedefinitions.hpp"
#include "server/Packet_handler.hpp"

struct ServerResources {
    std::thread packetHandler;
    PacketQueue received;
    PacketQueue toSend;

    Packet_handler lobbyManager;
    ClientsRegister connectedClients;

    ServerResources() : lobbyManager(&received, &running_) {
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
