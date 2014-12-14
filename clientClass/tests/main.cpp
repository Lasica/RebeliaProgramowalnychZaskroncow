//plik użyty do testów klasy

#include "client.hpp"
#include <iostream>


int main(){
    Client teststr("testtt", 80, "127.0.0.1", IN_LOBBY, "");
    Client test("testtt", 80, teststr.getIpStr(), IN_LOBBY, "");
    std::cout   << test.getNickname()    << std::endl
                << test.getPort()        << std::endl
                << (test.getIp()).boost::asio::ip::address::to_string()
                << test.getGameID()  << std::endl;

    if(test.getState()==IN_LOBBY)
        std::cout << "IN_LOBBY" << std::endl;
    else if(test.getState()==IN_GAME)
        std::cout << "IN_GAME" << std::endl;
    else
        std::cout << "setGameID() problem" << std::endl;

    if(test.isInGame())
        std::cout << "isInGame(): IN_GAME\n";
    else
        std::cout << "isInGame(): not IN_GAME\n";



    test.setState(IN_GAME);
    test.setGameID("test aa");

    std::cout   << std::endl             << std::endl
                << test.getNickname()    << std::endl
                << test.getPort()        << std::endl
                << (test.getIp()).boost::asio::ip::address::to_string() << std::endl
                << test.getGameID()  << std::endl
                << std::endl;

    if(test.getState()==IN_LOBBY)
        std::cout << "IN_LOBBY" << std::endl;
    else if(test.getState()==IN_GAME)
        std::cout << "IN_GAME" << std::endl;
    else
        std::cout << "setGameID() problem" << std::endl;


    std::cout << "\n***Hello! Copy constructor here!***\n";

    Client copyTest(test);
    std::cout   << copyTest.getNickname()    << std::endl
                << copyTest.getPort()        << std::endl
                << (copyTest.getIp()).boost::asio::ip::address::to_string()
                << copyTest.getGameID()  << std::endl;

    if(copyTest.getState()==IN_LOBBY)
        std::cout << "IN_LOBBY" << std::endl;
    else if(copyTest.getState()==IN_GAME)
        std::cout << "IN_GAME" << std::endl;
    else
        std::cout << "setGameID() problem" << std::endl;

    if(copyTest.isInGame())
        std::cout << "isInGame(): IN_GAME\n";
    else
        std::cout << "isInGame(): not IN_GAME\n";

    return 0;
}
