#ifndef GAMEROOM_H
#define GAMEROOM_H

#include "GameRoomRaw.hpp"
#include "shared/Subject.hpp"
#include "server/ClientsRegister.hpp"
#include <boost/shared_ptr.hpp>

#include <list>

class GameRoom;
BOOST_CLASS_EXPORT_KEY(GameRoom)

//TODO: dziedziczenie public, czy protected? przy protected trzeba dopisać gettery/settery
//FIXME: dziedziczenie raczej protected. Gameroom tez powinien dziedziczyc po Subject - skoro mamy mechanizm obserwatora, uzywajmy go jak najczesciej. Mysle tez, ze mozna wykorzystac tamtejszą listę subskrybentów zamiast tej listy tutaj. W końcu jedynym

class GameRoom : public GameRoomRaw, public Subject {
public:
    /*
     * obiekty: ustawienia (parsowalne na lua):
     * dla przykladu: mapa, predkosci wezy,
     * stan: liczba graczy, maksymalna liczba graczy, lista graczy w pokoju, czy wystartowal czy nie
     * int: id_pokoju
     * string: nazwa gameroomu
     */

    // numOfPlayers_ ustawiam na 0, bo jest potem zwiększany w add_player
    GameRoom(ClientID host, std::string gameRoomName);
    /* :
        GameRoomRaw(gameRoomName, host, gameRoomCounter_++), register_(cReg) {
        add_player(host);
    }*/
    // dla serializacji
    GameRoom();

    virtual ~GameRoom();

    virtual void notify();

    void add_player(ClientID newPlayer);
    // TODO (w poniższej lub innej metodzie): kiedy usuwany jest host - cały GameRoom jest kasowany
    // TODO : o skasowaniu GameRoomu powinna decydowac klasa GameRoomsRegister.
    void remove_player(ClientID player);

    GameRoomID get_id() {
        return id;
    }
    unsigned int get_number_of_players() {
        return numOfPlayers;
    }



    // porównuje id GameRoomów
    //bool operator<(GameRoom &comp);
  private:
    static ClientsRegister& register_; // jeśli używamy ClientID do oznaczania graczy, to musimy mieć jakieś odniesienie do rejestru, w którym się znajdują


    static GameRoomID gameRoomCounter_;//licznik GameRoomów, potrzebny do inicjalizacji id_
};

#endif // GAMEROOM_H
