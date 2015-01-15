#include "typedefinitions.h"
#include "shared/GameRoom.h"
#include "server/Client.hpp"
#include "server/ClientDataRaw.h"

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
    for(auto &a: players_){
        remove_player(a);
    }
}

// najpierw trzeba sprawdzać, czy na tym serwerze są jeszcze wolne miejsca
void GameRoom::add_player(ClientPtr newPlayer) {
    players_.push_back(newPlayer);
    newPlayer->set_state(ClientState(ClientState::GAMEROOM, this->get_id()));
    playersNames.push_back(newPlayer->get_nickname());
    numOfPlayers_++;
}

void GameRoom::remove_player(ClientPtr player) {
    player->set_state(ClientState(ClientState::LOBBY, 0));
    playersNames.remove(player->get_nickname());
    players_.remove(player);
    numOfPlayers_--;
}

