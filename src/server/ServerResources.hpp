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

/*!
 *  Zawiera instancje wszystkich głównych klas serwera.
 *  Jest bazą dla klasy TcpServer.
 */



struct ServerResources {

    std::thread *packetHandler;
    PacketQueue received;           //! kolejka wszystkich, które przyszły do serwera

    Packet_handler lobbyManager;    //! ten funktor zarządza przychodzącymi z zewnątrz pakietami - przesyła je w odpowiednie miejsca
    AddressRegister registeredAddresses;    //! rejestr adresów, z których nawiązano połączenie z serwerem

    ClientsRegister connectedClients;   //! klienci aktualnie podłączeni do serwera
    ChatRegister registeredChat;        //! rejestr czatu - przechowuje wiadomości czatu
    GameRoomsRegister registeredRooms;  //! pokoje gry zarejestrowane na serwerze
    std::vector<Subject*> SubscriptionList; //! lista tematów obserwacji, które uaktualniają swój stan w czasie pracy serwera

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
