#ifndef GAMEROOM_H
#define GAMEROOM_H

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
#include <boost/serialization/list.hpp>         // dla serializacji std::list<>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "shared/typedefinitions.hpp"
#include "Resource.hpp"
#include "Observer.hpp"
#include "GameRoomRaw.hpp"
#include "server/Client.hpp"
#include "server/ClientsRegister.hpp"
#include <boost/shared_ptr.hpp>

#include <list>

class GameRoom;
BOOST_CLASS_EXPORT_KEY(GameRoom)

//TODO: dziedziczenie public, czy protected? przy protected trzeba dopisać gettery/settery
//FIXME: dziedziczenie raczej protected. Gameroom tez powinien dziedziczyc po Subject - skoro mamy mechanizm obserwatora, uzywajmy go jak najczesciej. Mysle tez, ze mozna wykorzystac tamtejszą listę subskrybentów zamiast tej listy tutaj. W końcu jedynym
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
    GameRoom(ClientID host, std::string gameRoomName, ClientsRegister& cReg) :
        GameRoomRaw(gameRoomName, host, gameRoomCounter_++), register_(cReg) {
        add_player(host);
    }

    // dla serializacji
    GameRoom() : GameRoomRaw(), register_(*(new ClientsRegister)) { } // register_ musi być zainicjalizowany obiektem, nie można mu podać nulla

    virtual ~GameRoom();


    void add_player(ClientID newPlayer);
    // TODO (w poniższej lub innej metodzie): kiedy usuwany jest host - cały GameRoom jest kasowany
    void remove_player(ClientID player);

// czy te metody będą używane?
    GameRoomID      get_id() {
        return id;
    }

    unsigned int    get_number_of_players() {
        return numOfPlayers;
    }

private:

    // problem - jeśli register_ jest referencją, to w domyślnym konstruktorze (dla serializacji) jest inicjaliowany pustym ClientsRegister
    // można register_ zastąpić sprytnym wskaźnikiem,
    ClientsRegister& register_; // jeśli używamy ClientID do oznaczania graczy, to musimy mieć jakieś odniesienie do rejestru, w którym się znajdują

    static GameRoomID gameRoomCounter_;//licznik GameRoomów, potrzebny do inicjalizacji id_

};

#endif // GAMEROOM_H
