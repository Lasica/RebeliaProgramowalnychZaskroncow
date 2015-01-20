#include "typedefinitions.hpp"
#include "shared/GameRoomRaw.hpp"

class GameRoomRaw;
BOOST_CLASS_EXPORT_IMPLEMENT(GameRoomRaw)


GameRoomRaw::GameRoomRaw() : host(-1), id(
        -1) { }    // host i id są const, więc muszą być inicjalizowane; domyślny konstruktor uzywany jest przy serializacji; podczas deserializacji oba pola dostają prawidłowe wartości

GameRoomRaw::GameRoomRaw(std::string name, ClientID hostID, GameRoomID GRId) : gameRoomName(name), host(hostID),
    numOfPlayers(0), id(GRId) {
    maxNumOfPlayers =
        5;
}
//TODO zmienic maksymalna liczbe graczy z 5 na zmienną.

GameRoomRaw::~GameRoomRaw() { }

std::string GameRoomRaw::show_content() {
    return ("** GameRoomRaw **, gameRoomName==" + gameRoomName + ", players'IDs:"
            + std::string([this]()->std::string { std::string temp(""); for(auto a : players) temp += std::to_string(a) + " "; return temp;}())
            + ", numOfPlayers==" + std::to_string(numOfPlayers) + ", maxNumOfPlayers==" + std::to_string(maxNumOfPlayers)
            + ", id==" + std::to_string(id) + "\n");
}
