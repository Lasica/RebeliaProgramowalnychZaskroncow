#include <set>
#include <utility>

#include "server/ClientsRegister.hpp"
#include "server/Client.hpp"


ClientsRegister::ClientsRegister() {
    ;
}

ClientsRegister &ClientsRegister::instance() {
    static ClientsRegister instance;
    return instance;
}

ClientsRegister::ClientIt ClientsRegister::register_client(std::string nick, short unsigned int port,
                                                                    std::string ip, statename state, std::string gameID) {
    ClientsRegister::ClientIt it = clients_.insert(Client(nick, port, ip, state, gameID)).first; // insert returns pair<ClientIt, bool>

    return it;
}

void ClientsRegister::remove_client(unsigned int id) {
    clients_.erase(look_up_with_id(id));
}

void ClientsRegister::remove_client(std::string nick) {
    clients_.erase(look_up_with_nickname(nick));
}


typedef std::set<Client>::iterator ClientIt;

// look_up  functions find object with given nick or id
ClientIt ClientsRegister::look_up_with_nickname(std::string nick) {
    for(auto it = clients_.begin(); it != clients_.end(); ++it) {
        if(it->get_nickname() == nick)
            return it;
    }

    return clients_.end();
}

ClientIt ClientsRegister::look_up_with_id(Client::ClientID id) {
    for(auto it = clients_.begin(); it != clients_.end(); ++it) {
        if(it->get_client_id() == id)
            return it;
    }

    return clients_.end();
}

// functions to change state of Client (IN_GAME or IN_LOBBY)
void ClientsRegister::change_state(Client::ClientID id, statename st){
    look_up_with_id(id)->set_state(st);
}

void ClientsRegister::change_state(std::string nick, statename st){
    look_up_with_nickname(nick)->set_state(st);
}
