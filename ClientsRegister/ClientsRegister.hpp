#ifndef CLIENTSREGISTER_HPP
#define CLIENTSREGISTER_HPP

#include <set>
#include "Client.hpp"


class ClientsRegister {
public:
    static ClientsRegister& instance(); // singleton

    void register_client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID);
    void remove_client(unsigned int id);    //specify client with an id
    void remove_client(std::string nick);   //or with a nick

private:
    ClientsRegister();
    ClientsRegister(ClientsRegister& copy) = delete;
    ClientsRegister& operator=(const ClientsRegister&) = delete;
    ~ClientsRegister();

    std::set<Client> clients_;

    typedef std::set<Client>::iterator ClientIt;
    ClientIt look_up_with_nickname(std::string);
    ClientIt look_up_with_id(unsigned int id);
};

#endif //CLIENTSREGISTER_HPP
