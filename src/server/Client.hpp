/*******************************************
***Klasa Client***

Ta klasa reprezentuje klientów (graczy), łączących się z serwerem.
Każdy gracz jest opisany przez parametry charakteryzujące:
# połączenie z serwerem (ip i port)
# aktualny stan gracza (w grze/lobby)
# nazwę gracza, jego unikalne ID i (ewentualnie) gry.

********************************************/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include "server/Address.hpp"
#include "shared/Observer.h"
#include "shared/typedefinitions.h"
#include "server/ClientDataRaw.h"

class Client : public Observer, public ClientDataRaw {
public:
    Client(std::string nick, Address address, ClientState state);
    // Client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID);
    Client(const Client& c);

    ~Client();

    ClientID                        get_client_id() const;
    ClientState                     get_state() const;
    std::string                     get_nickname() const { return nickname_; }
    Address                         get_address() const { return address_; }
    //bool                            is_in_game();            //true if state==IN_GAME OBSOLETE
    void                            set_state(ClientState s);

    bool                            operator<(const Client&) const;
    virtual void                    update(Resource *updateInfo);

private:
    const std::string               nickname_;
    const Address                   address_;

    static ClientID                 nextID_;
    //ClientState                     state_;
    //std::unique_ptr<ClientState>      state_;
};

#endif //CLIENT_HPP
