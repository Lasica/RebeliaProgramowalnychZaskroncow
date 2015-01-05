#include "Client.hpp"
#include <boost/asio.hpp>
#include <string>

// constructors & destructor
Client::ClientID Client::nextID_ = 0;

Client::Client(std::string nick, short unsigned int port, Address::IP ip, statename state, std::string gameID) :
    clientID_(Client::nextID_++), state_(new statename(state)), gameID_(gameID) {
    address.nickname = nick;
    address.port = port;
    address.ip = ip;
}

// dopóki nie znamy dokładnie typu Address::IP, nie można wybrać metody konwertującej std::string na Address::IP
//Client::Client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID):
//    address.nickname(nick), clientID_(Client::nextID_++), address.port(port), ip_(boost::asio::ip::address::from_string(ip)), state_(new statename(state)),
//    gameID_(gameID) {
//    ;
//}

// copy c-tor copy also the unique id of every client
Client::Client(const Client &c) :
    clientID_(c.get_client_id()), state_(new statename(*(c.state_))), gameID_(c.gameID_) {
    address.nickname = c.address.nickname;
    address.port = c.address.port;
    address.ip = c.address.ip;
}

Client::~Client() {
    ;
}


// get methods
Client::ClientID Client::get_client_id() const {
    return clientID_;
}

statename Client::get_state() const {
    return *state_;
}

std::string Client::get_game_id() const {
    return gameID_;
}

//set methods
void Client::set_state(statename s) const {
    state_.reset(new statename);
    *state_ = s;
}

void Client::set_game_id(std::string id) const {
    gameID_ = id;
}

//
bool Client::is_in_game() {
    if(*state_ == IN_GAME)
        return true;
    else
        return false;
}

//operator for std::set
bool Client::operator<(const Client &comp) const {
    if(this->address.ip != comp.address.ip) {
        if(this->address.ip < comp.address.ip)
            return true;
        else
            return false;
    } else if(this->address.nickname < comp.address.nickname)
        return true;
    else
        return false;

}


