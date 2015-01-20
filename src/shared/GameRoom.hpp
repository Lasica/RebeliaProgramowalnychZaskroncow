#ifndef GAMEROOM_H
#define GAMEROOM_H
//#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include "GameRoomRaw.hpp"
#include "server/ClientsRegister.hpp"
#include <boost/shared_ptr.hpp>

#include <list>

class GameRoom;
BOOST_CLASS_EXPORT_KEY(GameRoom)

//FIXME: dziedziczenie raczej protected.  tamtejszą listę subskrybentów zamiast tej listy tutaj. W końcu jedynym

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
    GameRoom(ClientID host, std::string gameRoomName);



    virtual ~GameRoom();

    void add_player(ClientID newPlayer);
    // TODO (w poniższej lub innej metodzie): kiedy usuwany jest host - cały GameRoom jest kasowany
    // TODO : o skasowaniu GameRoomu powinna decydowac klasa GameRoomsRegister.
    void remove_player(ClientID player);

    GameRoomID get_id() {
        return id;
    }

    std::string get_name() { return gameRoomName; }

    unsigned int get_number_of_players() {
        return numOfPlayers;
    }

    unsigned int get_max_number_of_players() { return maxNumOfPlayers; }

    ClientID get_host_id() const { return host; }

    GameRoomRaw get_raw_data();
  private:
    // dla serializacji
    GameRoom();
    friend class boost::serialization::access;
//    template<class Archive>
//    void serialize(Archive &ar, const unsigned int) {
//        ar.template register_type<GameRoom>();   //// może pomoże na: std::exception: unregistered void cast
//        ar &boost::serialization::base_object<GameRoomRaw>(*this);

//    }
    void deregister_player(ClientID player);
    static ClientsRegister& register_; // jeśli używamy ClientID do oznaczania graczy, to musimy mieć jakieś odniesienie do rejestru, w którym się znajdują


    static GameRoomID gameRoomCounter_;//licznik GameRoomów, potrzebny do inicjalizacji id_
};

#endif // GAMEROOM_H
