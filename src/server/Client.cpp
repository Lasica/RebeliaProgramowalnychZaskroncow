#include "Client.hpp"
#include "shared/Resource.h"
#include <boost/asio.hpp>
#include <string>

// constructors & destructor
ClientID Client::nextID_ = 0;

Client::Client( Address address, TcpPointer pointer, std::string nick) :
    ClientDataRaw(Client::nextID_++, nick, ClientState()), address_(address), connection_(pointer) {
}

// Client::Client(std::string nick, Address address, ClientState state, std::string gameID) :
//     clientID_(Client::nextID_++), state_(new ClientState(state)) {
//     address.nickname = nick;
//     address.port = port;
//     address.ip = ip;
// }
//
// dopóki nie znamy dokładnie typu Address::IP, nie można wybrać metody konwertującej std::string na Address::IP
//Client::Client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID):
//    address.nickname(nick), clientID_(Client::nextID_++), address.port(port), ip_(boost::asio::ip::address::from_string(ip)), state_(new statename(state)),
//    gameID_(gameID) {
//    ;
//}

// copy c-tor copy also the unique id of every client
Client::Client(const Client &c) :
    ClientDataRaw(c.clientID_, c.nickname_, c.state_), address_(c.address_), connection_(c.connection_) {
}

Client::~Client() {
}


// get methods
ClientID Client::get_client_id() const {
    return clientID_;
}

ClientState Client::get_state() const {
    return state_;
}

//set methods
void Client::set_state(ClientState s) {
    state_ = s;
}

// bool Client::is_in_game() {
//     if(*state_ == IN_GAME)
//         return true;
//     else
//         return false;
// }

//operator for std::set
bool Client::operator<(const Client &comp) const {
    return address_ < comp.address_;
}

// TODO
void Client::update(Resource *updateInfo) {
    Packet updatePackage(Packet::RESOURCE, address_, updateInfo);
    send(updatePackage);
}   // bez definicji tej metody nie kompiluje się Client

inline void Client::send(Packet &packet) {
    connection_->write(packet.get_data_streambuf()); //TODO: to be edited using streambufs
}
