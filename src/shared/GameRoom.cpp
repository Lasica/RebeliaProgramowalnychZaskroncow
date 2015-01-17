#include "typedefinitions.hpp"
#include "shared/GameRoom.hpp"
#include "server/ClientsRegister.hpp"

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
#include <boost/serialization/list.hpp>         // dla serializacji std::list<>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

// czy to potrzebne?
class GameRoom;
BOOST_CLASS_EXPORT_IMPLEMENT(GameRoom)

GameRoomID GameRoom::gameRoomCounter_ = 0;


GameRoom::~GameRoom() {
    for(auto a : players)
        remove_player(a);
}

// najpierw trzeba sprawdzać, czy na tym serwerze są jeszcze wolne miejsca
void GameRoom::add_player(ClientID newPlayer) {
    players.push_back(newPlayer);
    register_.change_state(newPlayer, ClientState(ClientState::GAMEROOM, this->get_id()));
    playersNames.push_back((register_.look_up_with_id(newPlayer))->get_nickname());
    numOfPlayers++;
}

void GameRoom::remove_player(ClientID player) {
    register_.change_state(player, ClientState(ClientState::LOBBY, 0));
    playersNames.remove(((register_.look_up_with_id(player))->get_nickname()));
    players.remove(player);
    numOfPlayers--;
}

