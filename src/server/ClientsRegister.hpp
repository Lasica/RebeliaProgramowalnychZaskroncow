#ifndef CLIENTSREGISTER_HPP
#define CLIENTSREGISTER_HPP

#include <string>
#include <set>
#include "server/Client.hpp"
#include "server/Address.hpp"
#include "shared/Subject.h"

class ClientsRegister {
  public:
    typedef std::set<Client>::iterator ClientIt;
    ClientsRegister();
    ~ClientsRegister() { }
    ClientIt register_client(Address address, TcpPointer pointer);
    //ClientIt register_client(std::string nick, short unsigned int port,
    //                             AddressIP ip, ClientState state, std::string gameID);  //returns registered client's iterator


    ClientIt look_up_with_id(ClientID id)    const;
    //ClientIt look_up_with_nickname(std::string nick) const;
    //ClientIt look_up_with_address(Address addr)      const;

    /*
     * Funkcje zmieniajace stan sa tymczasowo wykomentowane, gdyz nie sa uzywane
     * Prawdopodobnie zmieni sie kontener przechowywany z seta na unordered_map po ClientID
     * Decyzja do podjecia w momencie uzycia tych funkcji
     */
    //void change_state(ClientID id, ClientState state);
    //void change_state(std::string nick, ClientState state);
    //void change_state(ClientIt it, ClientState state);

    void remove_client(ClientID id);    //specify client with an id
    //void remove_client(std::string nick);   //or with a nick
    void remove_client(ClientIt it);

    ClientState get_state(const ClientIt &it)   const {
        return it->get_state();      // game Id is in state
    }
    int         get_size()                      const {
        return clients_.size();
    }

  private:
    ClientsRegister(ClientsRegister &copy) = delete;
    ClientsRegister &operator=(const ClientsRegister &) = delete;


    std::set<Client> clients_;

};

#endif //CLIENTSREGISTER_HPP
