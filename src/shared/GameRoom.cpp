#include "GameRoom.h"
#include "server/Client.hpp"
#include "server/ClientDataRaw.h"

GameRoom::~GameRoom() {
    for(auto a : players_)
        remove_player(a);
}

// najpierw trzeba sprawdzać, czy na tym serwerze są jeszcze wolne miejsca
void GameRoom::add_player(GameRoom::ClientPtr newPlayer) {
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

