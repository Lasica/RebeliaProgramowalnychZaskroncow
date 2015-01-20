#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include "typedefinitions.hpp"
#include "shared/GameRoom.hpp"
#include "server/Server.hpp"

BOOST_CLASS_EXPORT_IMPLEMENT(GameRoom)

GameRoomID GameRoom::gameRoomCounter_ = 0;
ClientsRegister &GameRoom::register_ = TcpServer::getInstance().connectedClients;

GameRoom::GameRoom() : GameRoomRaw() { }

GameRoom::GameRoom(ClientID host, std::string gameRoomName) :
    GameRoomRaw(gameRoomName, host, gameRoomCounter_++) {
    add_player(host);
}

GameRoom::~GameRoom() {
    for(auto a: players){
        deregister_player(a);       // zmiany stanów kolejnych graczy na LOBBY
    }
}

// najpierw trzeba sprawdzać, czy na tym serwerze są jeszcze wolne miejsca
void GameRoom::add_player(ClientID newPlayer) {
    players.push_back(newPlayer);
    register_.change_state(newPlayer, ClientState(ClientState::GAMEROOM, this->get_id())); // FIXME jeszcze nie sprawne
    ++numOfPlayers;
}

void GameRoom::deregister_player(ClientID player){
    register_.change_state(player, ClientState(ClientState::LOBBY, 0));
    --numOfPlayers;
}

void GameRoom::remove_player(ClientID player) {
    if (player != host){
        deregister_player(player);
        players.remove(player);
    }
    else {
        for(auto a: players) {
            deregister_player(a);
        }
        players.clear();
        host = std::numeric_limits<ClientID>::max();
    }
}

GameRoomRaw GameRoom::get_raw_data(){
    GameRoomRaw GRR;
    GRR.host=host;
    const_cast<GameRoomID&>(GRR.id)=id;
    GRR.players = players;
    GRR.numOfPlayers = numOfPlayers;
    GRR.maxNumOfPlayers = maxNumOfPlayers;
    return GRR;
}
