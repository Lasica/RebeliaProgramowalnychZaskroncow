#include "typedefinitions.hpp"
#include "shared/GameRoomRaw.hpp"

//#include <boost/serialization/base_object.hpp>
//#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
//#include <boost/serialization/list.hpp>         // dla serializacji std::list<>

//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>

// czy to potrzebne?
class GameRoomRaw;
BOOST_CLASS_EXPORT_IMPLEMENT(GameRoomRaw)
GameRoomRaw::GameRoomRaw() : host(-1), id(
        -1) { }    // host i id są const, więc muszą być inicjalizowane; domyślny konstruktor uzywany jest przy serializacji; podczas deserializacji oba pola dostają prawidłowe wartości

GameRoomRaw::GameRoomRaw(std::string name, ClientID hostID, GameRoomID GRId) : gameRoomName(name), host(hostID),
    numOfPlayers(0), id(GRId) {
    maxNumOfPlayers =
        5;    //id=0, bo ten konstruktor i tak jest wywoływany zawsze przez klasę GameRoom, gdzie to pole jest inicjalizowane z licznika
}
//TODO zmienic maksymalna liczbe graczy z 5 na zmienną.

GameRoomRaw::~GameRoomRaw() { }

std::string GameRoomRaw::show_content() {
    return ("** GameRoomRaw **, gameRoomName==" + gameRoomName + ", players'IDs:"
            + std::string([this]()->std::string { std::string temp(""); for(auto a : players) temp += std::to_string(a) + " "; return temp;}())
            + ", numOfPlayers==" + std::to_string(numOfPlayers) + ", maxNumOfPlayers==" + std::to_string(maxNumOfPlayers)
            + ", id==" + std::to_string(id) + "\n");
}
