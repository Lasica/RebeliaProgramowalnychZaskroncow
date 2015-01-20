#ifndef GAMEROOMRAW_H
#define GAMEROOMRAW_H

#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
#include <boost/serialization/list.hpp>         // dla serializacji std::list<>
#include "shared/Resource.hpp"
#include "shared/typedefinitions.hpp"
#include <string>
#include <list>

struct GameRoomRaw;
BOOST_CLASS_EXPORT_KEY(GameRoomRaw)

struct GameRoomRaw : public Resource {

    GameRoomRaw();//  host(-1), id(-1) - host i id są const, więc muszą być inicjalizowane; domyślny konstruktor uzywany jest przy serializacji; podczas deserializacji oba pola dostają prawidłowe wartości
    GameRoomRaw(std::string name, ClientID hostID, GameRoomID GRId);
    virtual ~GameRoomRaw();

    std::string             gameRoomName;

    ClientID                host;
    std::list<ClientID>     players;

    unsigned int            numOfPlayers;
    unsigned int            maxNumOfPlayers;

    const GameRoomID        id;   //id danego GameRoomu

    virtual Tag get_tag() {
        return GAMEROOM;
    }
    virtual std::string show_content();

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
        ar.template register_type<GameRoomRaw>();
        ar &boost::serialization::base_object<Resource>(*this);
        ar &host;
        ar &players;
        ar &numOfPlayers;
        ar &maxNumOfPlayers;
        ar &gameRoomName;
        ar &const_cast<GameRoomID&>(id);
    }
};

#endif // GAMEROOMRAW_H
