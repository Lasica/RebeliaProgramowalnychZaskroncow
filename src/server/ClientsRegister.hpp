#ifndef CLIENTSREGISTER_HPP
#define CLIENTSREGISTER_HPP

#include <string>
#include <set>
#include "Client.hpp"
#include "../shared/Subject.h"

class ClientsRegister : public Subject {
public:
    static ClientsRegister& instance(); // singleton


    //*** ma zwracać const iterator
    ClientID register_client(std::string nick, short unsigned int port,
                                 std::string ip, statename state, std::string gameID);  //returns registered client's unique ID
    void remove_client(unsigned int id);    //specify client with an id
    void remove_client(std::string nick);   //or with a nick

    void change_state(unsigned int id);

private:
    ClientsRegister();
    ClientsRegister(ClientsRegister& copy) = delete;
    ClientsRegister& operator=(const ClientsRegister&) = delete;

    std::set<Client> clients_;

    typedef std::set<Client>::iterator ClientIt;
    ClientIt look_up_with_nickname(std::string);
    ClientIt look_up_with_id(unsigned int id);
};

#endif //CLIENTSREGISTER_HPP
