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

enum statename{ IN_LOBBY, IN_GAME };

class Client {
public:
    Client(std::string nick, short unsigned int port, Address::IP ip, statename state, std::string gameID);
   // Client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID);
    Client(const Client& c);

    ~Client();

    Address                         address;        //nick, ip, port

    typedef unsigned int            ClientID;

    ClientID                        get_client_id() const;
    statename                       get_state() const;
    std::string                     get_game_id() const;

    bool                            is_in_game();            //true if state==IN_GAME

    void                            set_state(statename s) const;
    void                            set_game_id(std::string id) const;

    bool                            operator<(const Client&) const;

private:
    // const std::string               nickname_; // jest już w strukturze address, ale może powinno być tutaj?
    const unsigned int              clientID_;   //unique ID for every player
    static unsigned int             nextID_;

    mutable std::unique_ptr<statename>      state_;
    mutable std::string                     gameID_;     // set only if player is IN_GAME
};

#endif //CLIENT_HPP
