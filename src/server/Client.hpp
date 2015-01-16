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
#include "shared/TcpConnection.h"
#include "shared/Packet.hpp"

class Client : public Observer, public ClientDataRaw {
  public:
    // TODO: W klasie ClientDataRaw lub tutaj dodać inicjację ClientID_ z jakiegoś licznika
    Client( Address address, TcpPointer pointer=nullptr, std::string nick = "UNREGISTERED");
    Client(const Client &c);

    ~Client();

    ClientID                        get_client_id() const;
    ClientState                     get_state() const;
    std::string                     get_nickname() const { return nickname_; }
    Address                         get_address() const { return address_; }

    void                            set_state(ClientState s);
    bool                            operator<(const Client &) const;
    virtual void                    update(Resource *updateInfo);

  private:
    const Address                   address_;

    static ClientID                 nextID_;
    TcpPointer                      connection_;

    inline void                     send(Packet &packet);
};

#endif //CLIENT_HPP
