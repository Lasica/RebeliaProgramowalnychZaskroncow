#ifndef CLIENTSREGISTER_HPP
#define CLIENTSREGISTER_HPP

#include <string>
#include <map>

#include <boost/thread/shared_mutex.hpp>
#include "server/Client.hpp"
#include "server/Address.hpp"
#include "shared/typedefinitions.hpp"
#include "shared/Subject.hpp"


class ClientsRegister: public Subject {
public:
    ClientsRegister();
    ~ClientsRegister() { }
    ClientID register_client(const Address *address, TcpPointer pointer=nullptr, std::string nickname="UNREGISTERED");


    //ClientIt look_up_with_address(Address addr)     const; // nie ma i nie bedzie. mozna to ustalic na podstawie addressRegister.
    const ClientPtr look_up_with_id(ClientID id) const;
    void change_state(ClientID id, ClientState state);

    void remove_client(ClientID id);

    ClientState get_state(ClientID id) const;

    int get_size() const {
        return clients_.size();
    }

private:
    ClientsRegister(ClientsRegister &copy) = delete;
    ClientsRegister &operator=(const ClientsRegister &) = delete;

    std::map<ClientID, ClientPtr>          clients_;
    //ClientPtr                              lookUpper_;
    mutable boost::shared_mutex            access_;

    void notify();
};

#endif //CLIENTSREGISTER_HPP
