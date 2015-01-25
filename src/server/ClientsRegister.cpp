#include <map>
#include <utility>

#include <boost/thread/locks.hpp>

#include "ClientsRegister.hpp"
#include "Client.hpp"
#include "Address.hpp"
#include "shared/typedefinitions.hpp"
#include "server/ClientDataRaw.hpp"
#include "shared/Resource.hpp"

ClientsRegister::ClientsRegister() { }

ClientID ClientsRegister::register_client(const Address *address, TcpPointer pointer, std::string nickname) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    auto it = clients_.insert(std::pair<ClientID, ClientPtr>(address->owner, ClientPtr(new Client(address, pointer, nickname))));
    //zawiadomienie obserwatorów o nowym kliencie w rejestrze
    Packet p(Packet::UPDATED_RESOURCE, nullptr, new ClientDataRaw(*(it.first)->second));
    Subject::notify(p);
    return address->owner;
}

void ClientsRegister::remove_client(ClientID id) {
    //zawiadomienie obserwatorów o usunięciu klienta z rejestru
    Packet p(Packet::REMOVE_RESOURCE, nullptr, new ClientDataRaw(*look_up_with_id(id)));
    Subject::notify(p);
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
    Packet p(Packet::UPDATED_RESOURCE, nullptr, new ClientDataRaw(*clients_.at(id)));
    notify(p);
}

// void ClientsRegister::notify(const Resource* resource, const Packet::Tag tag){
//     for(Observer *o : obs_)
//        o->update(resource, tag);
// }

// wysyła pełną dane o wszystkich klientach
void ClientsRegister::synchronise(Observer* obs) {
    boost::shared_lock< boost::shared_mutex > lock(access_);
    for(auto a: clients_) {
        Packet p(Packet::UPDATED_RESOURCE, nullptr, new ClientDataRaw(*(a.second)));
        // woła update() tylko dla tego pojedynczego klienta
        obs->update(p);
    }
}


