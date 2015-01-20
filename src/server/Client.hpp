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
#include "shared/Observer.hpp"
#include "shared/typedefinitions.hpp"
#include "server/ClientDataRaw.hpp"
#include "shared/Packet.hpp"

class ClientsRegister;
class Client : public Observer, public ClientDataRaw {
public:

    Client( const Address *address, TcpPointer pointer=nullptr, std::string nick = "UNREGISTERED");
    Client(const Client &c);

    ~Client();

    ClientID                        get_client_id() const {
        return clientID_;
    }
    ClientState                     get_state() const {
        return state_;
    }
    std::string                     get_nickname() const {
        return nickname_;
    }
    const Address*                  get_address() const {
        return address_;
    }

    void                            set_state(ClientState s) {
        state_=s;
	if(state_.location == ClientState::LOBBY) 
		subscribe();
	else if (state_.location == ClientState::GAME) 
		unsubscribe();
    }
    bool                            operator<(const Client &) const;
    virtual void                    update(Resource *updateInfo, Packet::Tag* tag);

private:
    const Address*                  address_;
    
    inline void                     send(Packet &packet); // const?
    static ClientID                 nextID_;

    void subscribe();
    void unsubscribe();
};

#endif //CLIENT_HPP
