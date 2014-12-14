/*******************************************
***Klasa Client***

Ta klasa reprezentuje klientów (graczy), łączących się z serwerem.
Każdy gracz jest opisany przez parametry charakteryzujące:
# połączenie z serwerem (ip i port)
# aktualny stan gracza (w grze/lobby)
# nazwę gracza i (ewentualnie) gry.

********************************************/
#include <iostream>
#include <boost/asio.hpp>


enum statename{ IN_LOBBY, IN_GAME };

class Client {
public:
    Client(std::string nick, short unsigned int port, boost::asio::ip::address ip, statename state, std::string gameID);
    Client(std::string nick, short unsigned int port, std::string ip, statename state, std::string gameID);
    Client(const Client& c);

    ~Client();


    std::string getNickname();
    short unsigned int getPort();
    boost::asio::ip::address getIp();
    std::string getIpStr();
    statename getState();
    std::string getGameID();

    bool isInGame();            //true if state==IN_GAME

    void setState(statename s);
    void setGameID(std::string id);

private:
    const std::string nickname;
    const unsigned short int port;
    const boost::asio::ip::address ip;

    statename state;
    std::string gameID;     // set only if player is IN_GAME
};
