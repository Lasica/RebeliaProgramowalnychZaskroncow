//#include "typedefinitions.hpp"
//#include "shared/GameRoom.hpp"
//#include "server/ClientsRegister.hpp"

//#include <boost/serialization/base_object.hpp>
//#include <boost/serialization/export.hpp>       //makro BOOST_CLASS_EXPORT
//#include <boost/serialization/list.hpp>         // dla serializacji std::list<>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>



//#include <boost/archive/text_iarchive.hpp>
//#include <boost/archive/text_oarchive.hpp>
//#include "typedefinitions.hpp"
#include "shared/GameRoom.hpp"
//#include "server/ClientsRegister.hpp"
#include "server/Server.hpp"
BOOST_CLASS_EXPORT_IMPLEMENT(GameRoom)  // może pomoże na: std::exception: unregistered void cast

GameRoomID GameRoom::gameRoomCounter_ = 0;
ClientsRegister &GameRoom::register_ = TcpServer::getInstance().connectedClients;

GameRoom::GameRoom() : GameRoomRaw() { }

GameRoom::GameRoom(ClientID host, std::string gameRoomName) :
    GameRoomRaw(gameRoomName, host, gameRoomCounter_++) {
//    std::cout << "***GameRoom c-tor***\n";
    add_player(host); // *** błąd! *** -> jeśli to jest odkomentowane, to test się zawiesza
}

GameRoom::~GameRoom() {

   //czy to jest jeszcze potrzebne?
    for(auto a: players){
//        std::cout << "~GameRoom() - usuwanie graczy \n";
//        std::cout << a << std::endl;
        deregister_player(a);       // zmiany stanów kolejnych graczy na LOBBY
    }
//    std::cout << "~GameRoom() - koniec \n";
}

// najpierw trzeba sprawdzać, czy na tym serwerze są jeszcze wolne miejsca
void GameRoom::add_player(ClientID newPlayer) {
    players.push_back(newPlayer);
    register_.change_state(newPlayer, ClientState(ClientState::GAMEROOM, this->get_id())); // FIXME jeszcze nie sprawne
    ++numOfPlayers;
//    std::cout << "***add_player***\n";

}

void GameRoom::deregister_player(ClientID player){
    register_.change_state(player, ClientState(ClientState::LOBBY, 0));
//    std::cout << "***deregister***\n";
    //players.remove(player); // może inny typ argumentu?
    --numOfPlayers;
}

//trzeba zrobić oddzielną metodę do usuwania pojedynczego klienta z serwera
// a tę poniższą przerobić na wyrejestrowanie z serwera (powinno w niej zostać tylko to, co jest poniżej)
void GameRoom::remove_player(ClientID player) {
    if (player != host){
        deregister_player(player);
        players.remove(player);
//        std::cout << "***remove_player***\n";
    }
    // usuwanie hosta - zamyka GameRoom - podobnie jak w destruktorze wołana jest metoda deregister dla wszystkich graczy
    else {
        for(auto a: players) {
            deregister_player(a);
        }
        players.clear();
        const_cast<ClientID&>(host) = std::numeric_limits<ClientID>::max();
    }
}

GameRoomRaw GameRoom::get_raw_data(){
    GameRoomRaw GRR;
    const_cast<ClientID&>(GRR.host)=host;
    const_cast<GameRoomID&>(GRR.id)=id;

    GRR.players = players;
    GRR.numOfPlayers = numOfPlayers;
    GRR.maxNumOfPlayers = maxNumOfPlayers;
    return GRR;
}
