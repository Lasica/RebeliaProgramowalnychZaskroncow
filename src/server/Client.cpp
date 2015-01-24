#include "Client.hpp"
#include "shared/Resource.hpp"
#include "shared/TcpConnection.hpp"
#include <boost/asio.hpp>
#include <string>
#include "server/Server.hpp"

ClientID Client::nextID_ = 0;   //wartość 0 - gracz, który nie istnieje


Client::Client( const Address *address, TcpPointer /*pointer*/, std::string nick) :
     Observer(Observer::observerNextID++), ClientDataRaw(Client::nextID_++, nick, ClientState()), address_(address) {
    subscribe();
    if(address_ != nullptr) { // zalozenie jest, ze w zadnym innym miejscu poza ClientsRegister address_ == nullptr.
        address_->change_owner(clientID_);
//        address_->update_connection(pointer);
    }
}

Client::Client(const Client &c) :
   Observer(c.observerID), ClientDataRaw(c.clientID_, c.nickname_, c.state_), address_(c.address_){
}

Client::~Client() {
}


bool Client::operator<(const Client &comp) const {
    return clientID_ < comp.clientID_;
}

void Client::update(Resource *updateInfo, Packet::Tag tag) {
    Packet updatePackage(tag, address_, updateInfo);
    send(updatePackage);
}

inline void Client::send(Packet &packet) {
    address_->connection->write(packet.get_data_streambuf()); //TODO: to be edited using streambufs
}

void Client::subscribe(){
	std::vector<Subject*>::iterator it = TcpServer::pointer->SubscriptionList.begin();
	for(; it < TcpServer::pointer->SubscriptionList.end(); ++it)
		(*it)->addObserver(this);
}

void Client::unsubscribe(){
	std::vector<Subject*>::iterator it = TcpServer::pointer->SubscriptionList.begin();
	for(; it < TcpServer::pointer->SubscriptionList.end(); ++it)
		(*it)->eraseObserver(this);
}
