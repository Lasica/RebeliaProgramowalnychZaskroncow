#include "Client.hpp"
#include "shared/Resource.hpp"
#include "shared/TcpConnection.hpp"
#include <boost/asio.hpp>
#include <string>

ClientID Client::nextID_ = 0;

Client::Client( const Address *address, TcpPointer pointer, std::string nick) :
    ClientDataRaw(Client::nextID_++, nick, ClientState()), address_(address) {
    address_->change_owner(clientID_);
    address_->update_connection(pointer);
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

// podejrzewam ze domyslny konstruktor kopiujacy nam wystarczy
Client::Client(const Client &c) :
    ClientDataRaw(c.clientID_, c.nickname_, c.state_), address_(c.address_) {
}

Client::~Client() {
}


//operator for std::set
//bool Client::operator<(const Client &comp) const {
//    return address_ < comp.address_;
//}
bool Client::operator<(const Client &comp) const {
    return clientID_ < comp.clientID_;
}

// TODO
void Client::update(Resource *updateInfo) {
    Packet updatePackage(Packet::UPDATED_RESOURCE, address_, updateInfo);
    send(updatePackage);
}

inline void Client::send(Packet &packet) {
    address_->connection->write(packet.get_data_streambuf()); //TODO: to be edited using streambufs
}
