#include <set>
#include <utility>

#include "ClientsRegister.hpp"
#include "Client.hpp"


ClientsRegister::ClientsRegister() {
    ;
}

ClientsRegister &ClientsRegister::instance() {
    static ClientsRegister instance;
    return instance;
}

ClientID ClientsRegister::register_client(std::string nick, short unsigned int port,
        std::string ip, statename state, std::string gameID) {
    ClientsRegister::ClientIt it = clients_.insert(Client(nick, port, ip, state, gameID)).first; // insert returns pair<ClientIt, bool>

    return it->get_client_id();
}

void ClientsRegister::remove_client(unsigned int id) {
    clients_.erase(look_up_with_id(id));
}

void ClientsRegister::remove_client(std::string nick) {
    clients_.erase(look_up_with_nickname(nick));
}


typedef std::set<Client>::iterator ClientIt;

// funkcje look_up do poprawek - nie wiem, czy działają
ClientIt ClientsRegister::look_up_with_nickname(std::string nick) {
    for(auto it = clients_.begin(); it != clients_.end(); ++it) {
        if(it->get_nickname() == nick)
            return it;
    }

    return clients_.end();
}

ClientIt ClientsRegister::look_up_with_id(unsigned int id) {
    for(auto it = clients_.begin(); it != clients_.end(); ++it) {
        if(it->get_client_id() == id)
            return it;
    }

    return clients_.end();
}
