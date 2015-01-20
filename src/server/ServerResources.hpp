#ifndef SERVERRESOURCES_H
#define SERVERRESOURCES_H

#include <vector>
#include <chrono>
#include "shared/typedefinitions.hpp"
#include "server/Packet_handler.hpp"
#include "server/ClientsRegister.hpp"
#include "server/AddressRegister.hpp"

#include "server/GameRoomsRegister.hpp"
#include "shared/ChatRegister.hpp"

struct ServerResources {

    std::thread *packetHandler;
    PacketQueue received;

    Packet_handler lobbyManager;
    AddressRegister registeredAddresses;

   ClientsRegister connectedClients;
   ChatRegister registeredChat;
   GameRoomsRegister registeredRooms;
    std::vector<Subject*> SubscriptionList;

 const  std::vector<Subject*>& get_subscrible_list(){
	    return SubscriptionList;
    }

    ServerResources() : lobbyManager(&received, &running_) {
    }

    void init() {
       SubscriptionList.push_back(&connectedClients); 
       SubscriptionList.push_back(&registeredChat);
       SubscriptionList.push_back(&registeredRooms);
        packetHandler = new std::thread(lobbyManager);
    }
    virtual ~ServerResources() {
        running_ = false;
//        packetHandler->join();

    }

protected:
    bool running_;
};

#endif // SERVERRESOURCES_H
