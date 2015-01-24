#include <map>
#include <utility>

#include <boost/thread/locks.hpp>

#include "ClientsRegister.hpp"
#include "Client.hpp"
#include "Address.hpp"
#include "shared/typedefinitions.hpp"

ClientsRegister::ClientsRegister() { }

ClientID ClientsRegister::register_client(const Address *address, TcpPointer pointer, std::string nickname) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    auto it = clients_.insert(std::pair<ClientID, ClientPtr>(address->owner, ClientPtr(new Client(address, pointer, nickname))));
    //zawiadomienie obserwatorów o nowym kliencie w rejestrze
    //boost::scoped_ptr<Resource> notification( new ClientDataRaw(address->owner, nickname, ClientState(ClientState::LOBBY, 0)));
    boost::shared_ptr<Resource> notification( new ClientDataRaw(*(it.first)->second));
    notify(notification.get(), Packet::UPDATED_RESOURCE);
    return address->owner;
}

void ClientsRegister::remove_client(ClientID id) {
    //zawiadomienie obserwatorów o usunięciu klienta z rejestru
    //boost::shared_ptr<Resource> notification( new ClientDataRaw(id, clients_.at(id)->get_nickname(), ClientState()));
    boost::shared_ptr<Resource> notification( new ClientDataRaw(*look_up_with_id(id)));
    notify(notification.get(), Packet::REMOVE_RESOURCE);
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
    boost::shared_ptr<Resource> notification( new ClientDataRaw(*clients_.at(id)));
    notify(notification.get(), Packet::UPDATED_RESOURCE);
}

void ClientsRegister::notify(const Resource* resource, const Packet::Tag tag){
    for(Observer *o : obs_)
       o->update(resource, tag); 
}

// wysyła pełną dane o wszystkich klientach
void ClientsRegister::synchronise(Observer* obs) {
    for(auto a: clients_) {
        boost::scoped_ptr<Resource> notification( new ClientDataRaw(a.second->get_address()->owner, a.second->get_nickname(), a.second->get_state()));
        Packet::Tag tag(Packet::UPDATED_RESOURCE);
        // woła update() tylko dla tego pojedynczego klienta
        obs->update(notification.get(), tag);
    }
}


