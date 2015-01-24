#include "server/GameRoomsRegister.hpp"
#include <utility>

GameRoomsRegister::GameRoomsRegister(): Observer(Observer::observerNextID++) { }

GameRoomsRegister::~GameRoomsRegister() { }

GameRoomPtr GameRoomsRegister::add_game_room(ClientID host, std::string name) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    GameRoom *gr = new GameRoom(host, name);
    auto i = game_rooms_.insert(std::pair<GameRoomID, GameRoomPtr>(gr->get_id(), GameRoomPtr(gr)));
    boost::shared_ptr<Resource> notification( new GameRoomRaw(*(i.first)->second));
    notify(&*notification, Packet::UPDATED_RESOURCE);
    return GameRoomPtr(gr);
}

void GameRoomsRegister::remove_game_room(GameRoomID id) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    auto i = game_rooms_.find(id);
    boost::shared_ptr<Resource> notification( new GameRoomRaw(*(i->second)));
    notify(notification.get(), Packet::REMOVE_RESOURCE);
    game_rooms_.erase(i);
}

GameRoomPtr GameRoomsRegister::look_up_with_id(GameRoomID id) {
    boost::shared_lock< boost::shared_mutex > lock(access_);
    return game_rooms_.find(id)->second;
}

unsigned int GameRoomsRegister::get_size() {
    return game_rooms_.size();
}

void GameRoomsRegister::notify(const Resource* resources, const Packet::Tag tag) {
    for(Observer *o : obs_)
        o->update(resources, tag); 
}
