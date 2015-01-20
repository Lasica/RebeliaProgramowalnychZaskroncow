#include <map>
#include <utility>

#include <boost/thread/locks.hpp>

#include "ClientsRegister.hpp"
#include "Client.hpp"
#include "Address.hpp"
#include "shared/typedefinitions.hpp"

ClientsRegister::ClientsRegister() { /*std::cout << "***ClientsRegister c-tor***\n";  */}

ClientID ClientsRegister::register_client(const Address *address, TcpPointer pointer, std::string nickname) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    clients_.insert(std::pair<ClientID, ClientPtr>(address->owner, ClientPtr(new Client(address, pointer, nickname))));
    return address->owner;
}

void ClientsRegister::remove_client(ClientID id) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    clients_.erase(id);
}

const ClientPtr ClientsRegister::look_up_with_id(ClientID id) const {
    boost::unique_lock< boost::shared_mutex > lock(access_);

    if (clients_.find(id) != clients_.end())
        return clients_.at(id);
    else
        return ClientPtr(nullptr);
}

ClientState ClientsRegister::get_state(ClientID id) const {
    return look_up_with_id(id)->get_state();
}

// uwaga! funkcja std::map<>::at() rzuca wyjątkiem, jeśli nie ma w mapie szukanego obiektu
void ClientsRegister::change_state(ClientID id, ClientState st) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    clients_.at(id)->set_state(st);
}

void ClientsRegister::notify(Resource* resource, const Packet::Tag* tag){
    for(Observer *o : obs_)
       o->update(resource, tag); 
}

