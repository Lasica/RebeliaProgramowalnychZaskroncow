#ifndef CLIENTSREGISTER_HPP
#define CLIENTSREGISTER_HPP

#include <string>
#include <set>

#include <boost/thread/shared_mutex.hpp>

#include "server/Client.hpp"
#include "server/Address.hpp"
#include "shared/Subject.hpp"
#include "shared/typedefinitions.hpp"

class ClientsRegister {
  public:
    ClientsRegister();
    ~ClientsRegister() { }
    ClientIt register_client(const Address *address, TcpPointer pointer);


    ClientIt look_up_with_id(ClientID id)    const;
    ClientIt look_up_with_address(Address addr)      const; // TODO -- zoptymalizowac, zeby nie bylo liniowe

    /*
     * Funkcje zmieniajace stan sa tymczasowo wykomentowane, gdyz nie sa uzywane
     * Prawdopodobnie zmieni sie kontener przechowywany z seta na unordered_map po ClientID
     * Decyzja do podjecia w momencie uzycia tych funkcji
     */

    //void change_state(ClientID id, ClientState state);
    void change_state(ClientID id, ClientState state);

    //void change_state(ClientIt it, ClientState state);

    inline void remove_client(ClientID id);
    void remove_client(ClientIt it);

    ClientState get_state(const ClientIt &it)   const {
        return it->get_state();
    }
    int         get_size()                      const {
        return clients_.size();
    }

  private:
    ClientsRegister(ClientsRegister &copy) = delete;
    ClientsRegister &operator=(const ClientsRegister &) = delete;


    std::set<Client> clients_;
    mutable boost::shared_mutex access_;
};

#endif //CLIENTSREGISTER_HPP
