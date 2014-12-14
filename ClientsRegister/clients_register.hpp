#ifndef CLIENTS_REGISTER_HPP
#define CLIENTS_REGISTER_HPP

#include "client.hpp"


class ClientsRegister {
public:
    ClientRegister();   //singleton??
    ~ClientRegister();

    void register_client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID);
    void remove_client(unsigned int id);    //specify client with an id
    void remove_client(std::string nick);   //or with a nick

private:
    set<Client> clients_;

    typedef std::set<Client>::iterator ClientIt;
    ClientIt look_up_with_nickname(std::string);
    ClientIt look_up_with_id(unsigned int id);
};

#endif //CLIENTS_REGISTER_HPP
