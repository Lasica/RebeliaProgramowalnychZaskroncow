#ifndef GAMEROOM_H
#define GAMEROOM_H

#include "Resource.h"
#include "Observer.h"
#include "GameRoomRaw.h"
#include "server/Client.hpp"
#include <boost/shared_ptr.hpp>

#include <list>

class GameRoom : protected GameRoomRaw {
public:
    /*
     * obiekty: ustawienia (parsowalne na lua):
     * dla przykladu: mapa, predkosci wezy,
     * stan: liczba graczy, maksymalna liczba graczy, lista graczy w pokoju, czy wystartowal czy nie
     * int: id_pokoju
     * string: nazwa gameroomu
     */
    typedef boost::shared_ptr<Client> ClientPtr;

    GameRoom(ClientPtr host, std::string gameRoomName) : GameRoomRaw(gameRoomName), id_(gameRoomCounter_++), numOfPlayers_(1), host_(host) { }
    ~GameRoom();

    // może jednak zastosować iteratory z ClientsRegister?
    // albo ID klientów?
    void add_player(ClientPtr newPlayer);
    // TODO (w poniższej lub innej metodzie): kiedy usuwany jest host - cały GameRoom jest kasowany
    void remove_player(ClientPtr player);

    typedef int ID;
    ID get_id() { return id_; }


private:
    const ID id_;   //id danego GameRoomu
    unsigned int numOfPlayers_;

    // set czy lista?
    std::list<ClientPtr> players_;
    ClientPtr host_;    // ten gracz ma specjalne uprawnienia

    static ID gameRoomCounter_; //licznik GameRoomów, potrzebny do inicjalizacji id_

};

#endif // GAMEROOM_H
