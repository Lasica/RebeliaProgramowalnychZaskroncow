#ifndef SERVERRESOURCES_H
#define SERVERRESOURCES_H

#include <chrono>
#include "server/ClientsRegister.hpp"
#include "shared/typedefinitions.hpp"
#include "server/Packet_handler.hpp"
#include "server/AddressRegister.hpp"

struct ServerResources {

    std::thread *packetHandler;
    PacketQueue received;

    Packet_handler lobbyManager;
    ClientsRegister connectedClients;
    AddressRegister registeredAddresses;

    ServerResources() : lobbyManager(&received, &running_) {
    }

    void init() {
<<<<<<< HEAD
        running_ = true;
        packetHandler = std::thread(lobbyManager);
    }
    virtual ~ServerResources() {
        running_ = false;
        packetHandler.join();
=======
        packetHandler = new std::thread(lobbyManager);
    }
    virtual ~ServerResources() {
        running_ = false;
//        packetHandler->join();
>>>>>>> master
    }

protected:
    bool running_;
};

#endif // SERVERRESOURCES_H
