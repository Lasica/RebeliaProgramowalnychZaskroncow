//#include "typedefinitions.hpp"
//#include "shared/GameRoom.hpp"
//#include "server/ClientsRegister.hpp"

//#include <boost/serialization/base_object.hpp>
//#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
//#include <boost/serialization/list.hpp>         // dla serializacji std::list<>

//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include "typedefinitions.hpp"
#include "shared/GameRoom.hpp"
//#include "server/ClientsRegister.hpp"
#include "server/Server.hpp"
//BOOST_CLASS_EXPORT_IMPLEMENT(GameRoom)

GameRoomID GameRoom::gameRoomCounter_ = 0;
ClientsRegister &GameRoom::register_ = TcpServer::getInstance().connectedClients;

GameRoom::GameRoom() : GameRoomRaw() { }

GameRoom::GameRoom(ClientID host, std::string gameRoomName) :
    GameRoomRaw(gameRoomName, host, gameRoomCounter_++) {
    add_player(host); // *** błąd! *** -> jeśli to jest odkomentowane, to test się zawiesza
}

GameRoom::~GameRoom() {
    for(auto a : players)
        remove_player(a);
}

// najpierw trzeba sprawdzać, czy na tym serwerze są jeszcze wolne miejsca
void GameRoom::add_player(ClientID newPlayer) {
    players.push_back(newPlayer);
    //register_.change_state(newPlayer, ClientState(ClientState::GAMEROOM, this->get_id())); // FIXME jeszcze nie sprawne
    ++numOfPlayers;
}

void GameRoom::remove_player(ClientID player) {
    register_.change_state(player, ClientState(ClientState::LOBBY, 0));
    players.remove(player);
    --numOfPlayers;
}
