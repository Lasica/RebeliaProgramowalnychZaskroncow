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


enum statename{ IN_LOBBY, IN_GAME };

class Client {
public:
    Client(std::string nick, short unsigned int port, boost::asio::ip::address ip, statename state, std::string gameID);
    Client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID);
    Client(const Client& c);

    ~Client();

    typedef unsigned int            ClientID;

    std::string                     get_nickname() const;
    ClientID                        get_client_id() const;
    short unsigned int              get_port() const;
    boost::asio::ip::address        get_ip() const;
    std::string                     get_ip_str() const;
    statename                       get_state() const;
    std::string                     get_game_id() const;

    bool                            is_in_game();            //true if state==IN_GAME

    void                            set_state(statename s) const;
    void                            set_game_id(std::string id) const;

    bool                            operator<(const Client&) const;

private:
    const std::string               nickname_;
    const unsigned int              clientID_;   //unique ID for every player
    static unsigned int             nextID_;

    const unsigned short int        port_;
    const boost::asio::ip::address  ip_;


    mutable std::unique_ptr<statename>      state_;
    mutable std::string                     gameID_;     // set only if player is IN_GAME
};

#endif //CLIENT_HPP
