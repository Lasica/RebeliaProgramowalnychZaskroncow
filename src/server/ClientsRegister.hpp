#ifndef CLIENTSREGISTER_HPP
#define CLIENTSREGISTER_HPP

#include <string>
#include <set>
#include "server/Client.hpp"
#include "server/Address.hpp"
#include "shared/Subject.h"


class ClientsRegister : public Subject {
public:
    typedef std::set<Client>::iterator ClientIt;
    ClientsRegister();
    ~ClientsRegister() { }

    ClientIt register_client(std::string nick, short unsigned int port,
                                 Address::IP ip, statename state, std::string gameID);  //returns registered client's iterator


    ClientIt look_up_with_id(Client::ClientID id)    const;
    ClientIt look_up_with_nickname(std::string nick) const;
    ClientIt look_up_with_address(Address addr)      const;

    void change_state(Client::ClientID id, statename state);
    void change_state(std::string nick, statename state);
    void change_state(ClientIt it, statename state);

    void remove_client(Client::ClientID id);    //specify client with an id
    void remove_client(std::string nick);   //or with a nick
    void remove_client(ClientIt it);

    statename   get_state(const ClientIt &it)   const { return it->get_state();   }
    std::string get_game_ID(const ClientIt &it) const { return it->get_game_id(); }
    int         get_size()                      const { return clients_.size();   }

private:
    ClientsRegister(ClientsRegister& copy) = delete;
    ClientsRegister& operator=(const ClientsRegister&) = delete;


    std::set<Client> clients_;

};

#endif //CLIENTSREGISTER_HPP
