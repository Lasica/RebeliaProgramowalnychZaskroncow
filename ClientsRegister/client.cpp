#include "client.hpp"
#include <boost/asio.hpp>


// constructors & destructor
Client::Client(std::string nick, short unsigned int port, boost::asio::ip::address ip, statename state, std::string gameID) :
    nickname_(nick), clientID_(nextID_++), port_(port), ip_(ip), state_(state), gameID_(gameID) {
    ;
}


Client::Client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID):
    nickname_(nick), clientID_(nextID_++), port_(port), ip_(boost::asio::ip::address::from_string(ip)), state_(state), gameID_(gameID) {
    ;
}

Client::Client(const Client &c) :
    nickname_(c.nickname_), clientID_(nextID_++), port_(c.port_), ip_(c.ip_), state_(c.state_), gameID_(c.gameID_) {
    ;
}

Client::~Client() {
    ;
};


// get methods
std::string Client::get_nickname() {
    return nickname_;
}

unsigned int Client::get_client_id(){
    return clientID_;
}

short unsigned int Client::get_port() {
    return port_;
}

boost::asio::ip::address Client::get_ip() {
    return ip_;
}

std::string Client::get_ip_str() {
    return ip_.boost::asio::ip::address::to_string();
}

statename Client::get_state() {
    return state_;
}

std::string Client::get_game_id() {
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
bool operator<(const Client& a, const Client& b){
    if(a.get_ip_str()!=b.get_ip_str()){
        if(a.get_ip_str()<b.get_ip_str()){
            return true
        }; else {
            return false;
        };
    } else if(a.get_nickname()<b.get_nickname()){
        return true;
    } else {
        return false;
    }

}


