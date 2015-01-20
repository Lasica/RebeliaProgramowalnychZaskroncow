#ifndef CLIENTSREGISTER_HPP
#define CLIENTSREGISTER_HPP

#include <string>
#include <set>

#include <boost/thread/shared_mutex.hpp>
#include "server/Client.hpp"
#include "server/Address.hpp"
#include "shared/typedefinitions.hpp"
#include "shared/Subject.hpp"
struct client_comparator {
    bool operator()(const ClientPtr &a, const ClientPtr &b) const {
        return a->clientID_ < b->clientID_;
    }
};

class ClientsRegister: public Subject {
public:
    ClientsRegister();
    ~ClientsRegister() { }
    ClientIt register_client(const Address *address, TcpPointer pointer);


    ClientIt look_up_with_id(ClientID id)           const;
    //ClientIt look_up_with_address(Address addr)     const; // nie ma i nie bedzie. mozna to ustalic na podstawie addressRegister.

    void change_state(ClientID id, ClientState state);

    inline void remove_client(ClientID id);
    void        remove_client(ClientIt it);

    ClientState get_state(const ClientIt &it) const {
        return (*it)->state_;
    }
    int get_size() const {
        return clients_.size();
    }

private:
    ClientsRegister(ClientsRegister &copy) = delete;
    ClientsRegister &operator=(const ClientsRegister &) = delete;

    std::set<ClientPtr, client_comparator> clients_;
    ClientPtr                              lookUpper_;
    mutable boost::shared_mutex            access_;

     void notify(Resource*,const Packet::Tag*);
    };

#endif //CLIENTSREGISTER_HPP
