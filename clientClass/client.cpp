#include "client.hpp"
#include <boost/asio.hpp>


// constructors & destructor
Client::Client(std::string nick, short unsigned int port, boost::asio::ip::address ip, statename state, std::string gameID) :
    nickname(nick), port(port), ip(ip), state(state), gameID(gameID) {
    ;
}


Client::Client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID):
    nickname(nick), port(port), ip(boost::asio::ip::address::from_string(ip)), state(state), gameID(gameID) {
    ;
}

Client::Client(const Client &c) :
    nickname(c.nickname), port(c.port), ip(c.ip), state(c.state), gameID(c.gameID) {
    ;
}

Client::~Client() {
    ;
};


// get methods
std::string Client::getNickname() {
    return nickname;
}

short unsigned int Client::getPort() {
    return port;
}

boost::asio::ip::address Client::getIp() {
    return ip;
}

std::string Client::getIpStr() {
    return ip.boost::asio::ip::address::to_string();
}

statename Client::getState() {
    return state;
}

std::string Client::getGameID() {
    return gameID;
}

//set methods
void Client::setState(statename s) {
    state = s;
}

void Client::setGameID(std::string id) {
    gameID = id;
}

//
bool Client::isInGame() {
    if(state == IN_GAME)
        return true;
    else
        return false;
}



