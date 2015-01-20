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

/*!
*   Ta klasa reprezentuje klientów (graczy), łączących się z serwerem.
*   Klienci są powiadamiani o zmianach w grze przez tematy obserwacji (metodą update).
*/

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
    virtual void                    update(Resource *updateInfo, Packet::Tag* tag); //!< metoda wywoływana przez temat obserwacji, gdy nastąpi zmiana w środowisku gracza

private:
    const Address*                  address_;
    
    inline void                     send(Packet &packet); // const?
    static ClientID                 nextID_;

    void subscribe();
    void unsubscribe();
};

#endif //CLIENT_HPP
