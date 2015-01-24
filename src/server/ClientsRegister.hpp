#ifndef CLIENTSREGISTER_HPP
#define CLIENTSREGISTER_HPP

#include <string>
#include <map>
#include <boost/thread/shared_mutex.hpp>
#include "server/Client.hpp"
#include "server/Address.hpp"
#include "shared/typedefinitions.hpp"
#include "shared/Subject.hpp"

/*!
 *  Ta klasa jest rejestrem klientów - jest wykorzystywana do zarządzania graczami podłączonymi do serwera.
 *  Pozwala dodawać, usuwać, zmieniać stan klientów.
 */

class ClientsRegister: public Subject {
public:
    ClientsRegister();
    ~ClientsRegister() { }
    ClientID register_client(const Address *address, TcpPointer pointer=nullptr, std::string nickname="UNREGISTERED"); //! metoda rejestrująca nowego klienta na serwerze

    const ClientPtr look_up_with_id(ClientID id) const;     //! wyszukiwanie klientów po zadanym id
    void change_state(ClientID id, ClientState state);      //! metoda zmieniająca stan (miejsce "pobytu") klienta

    void remove_client(ClientID id);                        //! usuwanie klienta z serwera

    ClientState get_state(ClientID id) const;

    int get_size() const {                                  //! mówi ile jest graczy na serwerze
        return clients_.size();
    }
    virtual void synchronise(Observer* obs);

private:
    ClientsRegister(ClientsRegister &copy) = delete;
    ClientsRegister &operator=(const ClientsRegister &) = delete;

    std::map<ClientID, ClientPtr>          clients_;
    mutable boost::shared_mutex            access_;

//      void notify(const Resource*,const Packet::Tag);
    };

#endif //CLIENTSREGISTER_HPP
