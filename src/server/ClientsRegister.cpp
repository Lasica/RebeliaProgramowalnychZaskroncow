#include <set>
#include <utility>

#include "ClientsRegister.hpp"
#include "Client.hpp"
#include "Address.hpp"


ClientsRegister::ClientsRegister() {
    ;
}

ClientsRegister::ClientIt ClientsRegister::register_client(std::string nick, Address address, ClientState state) {
    ClientsRegister::ClientIt it = clients_.insert(Client(nick, address, state)).first; // insert returns pair<ClientIt, bool>

    return it;
}

void ClientsRegister::remove_client(unsigned int id) {
    clients_.erase(look_up_with_id(id));
}
/*
void ClientsRegister::remove_client(std::string nick) {
    clients_.erase(look_up_with_nickname(nick));
}*/

void ClientsRegister::remove_client(ClientIt it) {
    clients_.erase(it);
}


typedef std::set<Client>::iterator ClientIt;

// look_up  functions find object with given nick or id
/*ClientIt ClientsRegister::look_up_with_nickname(std::string nick) const {
    for(auto it = clients_.begin(); it != clients_.end(); ++it) {
        if(it->address.nickname == nick)
            return it;
    }

    return clients_.end();
}*/

ClientIt ClientsRegister::look_up_with_id(ClientID id) const {
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
// void ClientsRegister::change_state(ClientID id, ClientState st) {
//     look_up_with_id(id)->set_state(st);
// }
//
//
// void ClientsRegister::change_state(std::string nick, ClientState st) {
//     look_up_with_nickname(nick)->set_state(st);
// }
//
// void ClientsRegister::change_state(ClientIt it, ClientState st) {
//     it->set_state(st);
// }
