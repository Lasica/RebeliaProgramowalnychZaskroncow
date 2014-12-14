#include "clients_register.hpp"
#include "client.hpp"
#include <set>

ClientsRegister();
~ClientsRegister();

void ClientsRegister::register_client(std::string nick, short unsigned int port,
                std::string ip, statename state, std::string gameID){
    clients_.insert(Client(nick, port, ip, state, gameID));
}

void ClientsRegister::remove_client(unsigned int id){
    clients_.erase(look_up_with_id(id));
}

void ClientsRegister::remove_client(std::string nick){
    clients_.erase(look_up_with_nickname(nick));
}

ClientIt ClientsRegister::look_up_with_nickname(std::string nick){
    for(auto &a: clients_){
        if(a.get_nickname()==nick){
            return a;
        }
    }

    return clients_.end;
}

ClientIt ClientsRegister::look_up_with_id(unsigned int id){
    for(auto &a: clients_){
        if(a.get_id()==id){
            return a;
        }
    }

    return clients_.end;
}
