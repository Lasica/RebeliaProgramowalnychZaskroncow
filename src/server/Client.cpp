#include "Client.hpp"
#include <boost/asio.hpp>


// constructors & destructor
unsigned int Client::nextID_ = 0;

Client::Client(std::string nick, short unsigned int port, boost::asio::ip::address ip, statename state, std::string gameID) :
    nickname_(nick), clientID_(Client::nextID_++), port_(port), ip_(ip), state_(state), gameID_(gameID) {
    ;
}


Client::Client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID):
    nickname_(nick), clientID_(Client::nextID_++), port_(port), ip_(boost::asio::ip::address::from_string(ip)), state_(state), gameID_(gameID) {
    ;
}

// copy c-tor copy also the unique id of every client
Client::Client(const Client &c) :
    nickname_(c.nickname_), clientID_(c.get_client_id()), port_(c.port_), ip_(c.ip_), state_(c.state_), gameID_(c.gameID_) {
    ;
}

Client::~Client() {
    ;
};


// get methods
std::string Client::get_nickname() const {
    return nickname_;
}

ClientID Client::get_client_id() const {
    return clientID_;
}

short unsigned int Client::get_port() const {
    return port_;
}

boost::asio::ip::address Client::get_ip() const {
    return ip_;
}

std::string Client::get_ip_str() const {
    return ip_.boost::asio::ip::address::to_string();
}

statename Client::get_state() const {
    return state_;
}

std::string Client::get_game_id() const {
    return gameID_;
}

//set methods
void Client::set_state(statename s) {
    state_ = s;
}

void Client::set_game_id(std::string id) {
    gameID_ = id;
}

//
bool Client::is_in_game() {
    if(state_ == IN_GAME)
        return true;
    else
        return false;
}

//operator for std::set
bool Client::operator<(const Client &comp) const {
    if(this->get_ip_str() != comp.get_ip_str()) {
        if(this->get_ip_str() < comp.get_ip_str())
            return true;
        else
            return false;
    } else if(this->get_nickname() < comp.get_nickname())
        return true;
    else
        return false;

}


