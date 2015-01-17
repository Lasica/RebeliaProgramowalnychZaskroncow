#include "shared/GameRoomsRegister.hpp"
#include <utility>

GameRoomsRegister::GameRoomsRegister() { }

GameRoomsRegister::~GameRoomsRegister() { }

GameRoomPtr GameRoomsRegister::add_game_room(ClientID host, std::string name){
    // zabezpieczyć mutexem?
    GameRoom* gr = new GameRoom(host, name);
    game_rooms_.insert(std::pair<GameRoomID, GameRoomPtr>(gr->get_id(), GameRoomPtr(gr)));
    return GameRoomPtr(gr);
}

void GameRoomsRegister::remove_game_room(GameRoomID id){
    // zabezpieczyć mutexem?
    game_rooms_.erase(game_rooms_.find(id));
}

GameRoomPtr GameRoomsRegister::look_up_with_id(GameRoomID id){
    return game_rooms_.find(id)->second;
}

unsigned int GameRoomsRegister::get_size() {
    return game_rooms_.size();
}
