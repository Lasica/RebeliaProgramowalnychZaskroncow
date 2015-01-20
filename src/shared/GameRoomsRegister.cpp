#include "shared/GameRoomsRegister.hpp"
#include <utility>

GameRoomsRegister::GameRoomsRegister() { }

GameRoomsRegister::~GameRoomsRegister() { }

GameRoomPtr GameRoomsRegister::add_game_room(ClientID host, std::string name) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    GameRoom *gr = new GameRoom(host, name);
    game_rooms_.insert(std::pair<GameRoomID, GameRoomPtr>(gr->get_id(), GameRoomPtr(gr)));
    return GameRoomPtr(gr);
}

void GameRoomsRegister::remove_game_room(GameRoomID id) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    game_rooms_.erase(game_rooms_.find(id));
}

GameRoomPtr GameRoomsRegister::look_up_with_id(GameRoomID id) {
    boost::shared_lock< boost::shared_mutex > lock(access_);
    return game_rooms_.find(id)->second;
}

unsigned int GameRoomsRegister::get_size() {
    return game_rooms_.size();
}

void GameRoomsRegister::notify() {
    for(Observer *o : obs_);
        //o->update(&(chatLog_.back())); Co przesyłać dla obserwatora?
}

