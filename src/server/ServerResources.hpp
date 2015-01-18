#ifndef SERVERRESOURCES_H
#define SERVERRESOURCES_H

#include <vector>
#include <chrono>
#include "server/ClientsRegister.hpp"
#include "shared/typedefinitions.hpp"
#include "server/Packet_handler.hpp"
#include "server/AddressRegister.hpp"
//TODO #include "shared/GameRoomsRegister.hpp"
//TODO #include "shared/ChatRegister.hpp"
#include "shared/Subject.hpp"
struct ServerResources {

    std::thread *packetHandler;
    PacketQueue received;

    Packet_handler lobbyManager;
    AddressRegister registeredAddresses;

   ClientsRegister connectedClients;
 //TODO   ChatRegister registeredChat; 
   //TODO GameRoomsRegister registeredRooms;
    std::vector<Subject*> SubscriptionList;

    std::vector<Subject*> get_subscrible_list(){
	    return SubscriptionList;
    }

    ServerResources() : lobbyManager(&received, &running_) {
    }

    void init() {
       SubscriptionList.push_back(&connectedClients); 
    //TODO  SubscriptionList.push_back(&registeredChat); 
      //TODO SubscriptionList.push_back(&registeredRooms); 
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
