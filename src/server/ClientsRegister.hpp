#ifndef CLIENTSREGISTER_HPP
#define CLIENTSREGISTER_HPP

#include <string>
#include <set>
#include "Client.hpp"
#include "../shared/Subject.h"

class ClientsRegister : public Subject {
public:
    typedef std::set<Client>::iterator ClientIt;
    //typedef std::set<Client>::const_iterator ClientConstIt;

    static ClientsRegister& instance(); // singleton

    ClientIt register_client(std::string nick, short unsigned int port,
                                 std::string ip, statename state, std::string gameID);  //returns registered client's unique ID

    ClientIt look_up_with_id(Client::ClientID id);
    ClientIt look_up_with_nickname(std::string nick);

    void change_state(Client::ClientID id, statename state);
    void change_state(std::string nick,statename state);

    void remove_client(Client::ClientID id);    //specify client with an id
    void remove_client(std::string nick);   //or with a nick

private:
    ClientsRegister();
    ClientsRegister(ClientsRegister& copy) = delete;
    ClientsRegister& operator=(const ClientsRegister&) = delete;

    std::set<Client> clients_;

};

#endif //CLIENTSREGISTER_HPP
