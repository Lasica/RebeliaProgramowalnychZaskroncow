#include <set>
#include <utility>

#include <boost/thread/locks.hpp>

#include "ClientsRegister.hpp"
#include "Client.hpp"
#include "Address.hpp"
#include "shared/typedefinitions.hpp"

ClientsRegister::ClientsRegister() : lookUpper_(new Client(nullptr)) { }

ClientIt ClientsRegister::register_client(const Address *address, TcpPointer pointer) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    ClientIt it = clients_.insert(ClientPtr(new Client(address, pointer))).first;
    return it;
}

inline void ClientsRegister::remove_client(unsigned int id) {
    remove_client(look_up_with_id(id));
}

void ClientsRegister::remove_client(ClientIt it) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    clients_.erase(it);
}

ClientIt ClientsRegister::look_up_with_id(ClientID id) const {
    static ClientID &lookUpID=const_cast<ClientID&>(lookUpper_->clientID_);

    boost::shared_lock< boost::shared_mutex > lock(access_);
    lookUpID = id;
    return clients_.find(lookUpper_);
}

void ClientsRegister::change_state(ClientID id, ClientState st) {
    (*look_up_with_id(id))->set_state(st);
}

void ClientsRegister::notify() {
    for(Observer *o : obs_);
      //!!  o->update(&(chatLog_.back())); Co przekazywać obserwtorowi?
}

