#include "server/GameRoomsRegister.hpp"
#include <utility>

GameRoomsRegister::GameRoomsRegister()/*: Observer(Observer::observerNextID++)*/ { }

GameRoomsRegister::~GameRoomsRegister() { }

GameRoomPtr GameRoomsRegister::add_game_room(ClientID host, std::string name) {
    std::cout << "* Tworzenie pokoju: " << name << "\n";

    boost::unique_lock< boost::shared_mutex > lock(access_);
    GameRoom *gr = new GameRoom(host, name);
    auto i = game_rooms_.insert(std::pair<GameRoomID, GameRoomPtr>(gr->get_id(), GameRoomPtr(gr)));
    Packet p(Packet::UPDATED_RESOURCE, nullptr, new GameRoomRaw(*(i.first)->second));
    notify(p);
    return GameRoomPtr(gr);
}

void GameRoomsRegister::remove_game_room(GameRoomID id) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    auto i = game_rooms_.find(id);
    std::cout << "* Usuwanie pokoju: " << (*i).second->gameRoomName << "\n";

    Packet p(Packet::UPDATED_RESOURCE, nullptr, new GameRoomRaw(*(i->second)));
    notify(p);
    game_rooms_.erase(i);
}

GameRoomPtr GameRoomsRegister::look_up_with_id(GameRoomID id) {
    boost::shared_lock< boost::shared_mutex > lock(access_);
    return game_rooms_.find(id)->second;
}

unsigned int GameRoomsRegister::get_size() {
    return game_rooms_.size();
}

// void GameRoomsRegister::notify(const Resource* resources, const Packet::Tag tag) {
//     for(Observer *o : obs_)
//         o->update(resources, tag);
// }

// wysyła pełną dane o wszystkich klientach
void GameRoomsRegister::synchronise(Observer* obs) {
    std::cout << "* Synchronizacja rejestru pokojów gry u klienta o nicku: " << static_cast<Client*>(obs)->get_nickname() << "\n";

    boost::shared_lock< boost::shared_mutex > lock(access_);   
    for(auto a: game_rooms_) {
        Packet p(Packet::UPDATED_RESOURCE, nullptr, new GameRoomRaw(*a.second));
        // woła update() tylko dla tego pojedynczego obserwatora
        obs->update(p);
    }
}

