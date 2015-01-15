#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
#include <boost/serialization/list.hpp>         // dla serializacji std::list<>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "shared/typedefinitions.h"
#include "Resource.h"
#include "Observer.h"
#include "GameRoomRaw.h"
#include "server/Client.hpp"
#include <boost/shared_ptr.hpp>

#include <list>

// czy to potrzebne?
class GameRoom;
BOOST_CLASS_EXPORT_KEY(GameRoom)

//TODO: dziedziczenie public, czy protected? przy protected trzeba dopisać gettery/settery
class GameRoom : public GameRoomRaw {
 public:
    /*
     * obiekty: ustawienia (parsowalne na lua):
     * dla przykladu: mapa, predkosci wezy,
     * stan: liczba graczy, maksymalna liczba graczy, lista graczy w pokoju, czy wystartowal czy nie
     * int: id_pokoju
     * string: nazwa gameroomu
     */

    // numOfPlayers_ ustawiam na 0, bo jest potem zwiększany w add_player
    GameRoom(ClientPtr host, std::string gameRoomName) :
        GameRoomRaw(gameRoomName), id_(gameRoomCounter_++),
        numOfPlayers_(0), host_(host) { add_player(host); }

    // dla serializacji
    GameRoom() : id_(-1) { }

    virtual ~GameRoom();

    // może jednak zastosować iteratory z ClientsRegister?
    // albo ID klientów?
    void add_player(ClientPtr newPlayer);
    // TODO (w poniższej lub innej metodzie): kiedy usuwany jest host - cały GameRoom jest kasowany
    void remove_player(ClientPtr player);

    GameRoomID      get_id() { return id_; }
    unsigned int    get_number_of_players() { return numOfPlayers_; }

    // ****************
    //UWAGA! Ta klasa i jej serializacja wymaga skrupulatnego przetestowania!
    // Kod się kompiluje, ale nie gwarantuję, że używanie tej klasy, a w szczególności jej serializacja
    // jest bezpieczna.
    //*****************
//    friend class boost::serialization::access;
//    template<class Archive>
//    void serialize(Archive &ar, const unsigned int) {
//        ar & boost::serialization::base_object<GameRoomRaw>(*this);

//        ar & const_cast<GameRoomID&>(id_);
//        ar & numOfPlayers_;
//    }


private:
    const GameRoomID id_;   //id danego GameRoomu
    unsigned int numOfPlayers_;

    std::list<ClientPtr> players_;
    ClientPtr host_;    // ten gracz ma specjalne uprawnienia

    static GameRoomID gameRoomCounter_; //licznik GameRoomów, potrzebny do inicjalizacji id_
};

#endif // GAMEROOM_H
