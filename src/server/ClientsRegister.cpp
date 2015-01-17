#include <set>
#include <utility>

#include <boost/thread/locks.hpp>

#include "ClientsRegister.hpp"
#include "Client.hpp"
#include "Address.hpp"
#include "shared/typedefinitions.hpp"

ClientsRegister::ClientsRegister() { }

ClientIt ClientsRegister::register_client(const Address *address, TcpPointer pointer) {
    boost::unique_lock< boost::shared_mutex > lock(access_);
    ClientIt it = clients_.insert(Client(address, pointer)).first;
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

    boost::shared_lock< boost::shared_mutex > lock(access_);
    for(auto it = clients_.begin(); it != clients_.end(); ++it) {
        if(it->get_client_id() == id)
            return it;
    }

    return clients_.end();

}
//
// ClientIt ClientsRegister::look_up_with_address(Address addr) const {
//     for(auto it = clients_.begin(); it != clients_.end(); ++it) {
//         if(it->get ==
//                 addr.nickname)   // jeśli będą problemy, to można dodać porównywanie ip i portów (to i tak nie pomoże)
//             return it;
//     }
//
//     return clients_.end();
// }
//
// // functions to change state of Client (IN_GAME or IN_LOBBY)
void ClientsRegister::change_state(ClientID id, ClientState st) {
    look_up_with_id(id)->set_state(st);
}


// void ClientsRegister::change_state(ClientIt it, ClientState st) {
//     it->set_state(st);
// }
