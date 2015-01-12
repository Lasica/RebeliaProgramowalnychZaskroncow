#include "GameRoom.h"

GameRoom::~GameRoom() {
    for(auto a: players_){
        remove_player(a);
    }
}

// najpierw trzeba sprawdzać, czy na tym serwerze są jeszcze wolne miejsca
void GameRoom::add_player(GameRoom::ClientPtr newPlayer) {
    players_.push_back(newPlayer);
    newPlayer->set_state(IN_GAMEROOM);
    newPlayer->set_game_id(gameRoomName);
    numOfPlayers_++;
    // TODO: kiedy będzie już można pobrać nickname z obiektu Client dodać go do listy nicków
    //playersNames.push_back(newPlayer-> ?? );
}

void GameRoom::remove_player(ClientPtr player) {
    player->set_game_id("");
    player->set_state(IN_LOBBY);
    // TODO: kiedy będzie już można pobrać nickname z obiektu Client usunąć go do listy nicków
    //playersNames.remove(newPlayer-> ?? );
    players_.remove(player);
    numOfPlayers_--;
}

