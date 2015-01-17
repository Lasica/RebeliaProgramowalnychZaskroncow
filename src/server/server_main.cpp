#include "server/Server.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

//#include "Logger.hpp"
using boost::asio::ip::tcp;
using namespace boost::asio;
int main() {
    io_service io;
    TcpServer &server = TcpServer::getInstance(io);
    server.start();
    //Logger::log_main() << "Serwer uruchomiony\n";
    std::cout << "Serwer uruchomiony\n";
    //Przykłady//////////////
    /*   server::TcpServer::ConIter it =
           server.getConIter(); //automatycznie wskazuje na połączenie nr 0 (w sumie ani to iterator ani wskaźnik, nie wiem)
       server::TcpServer::ConIter it2 = server.getConIter();
       ++it2;
       --it2;
       it = it + 2;
       it[0]; // działa jak klasyczny operator [], czyli zwraca połączenie spod indeksu 0, ale uwaga - tu pewne ulepszenie - dodatkowo ustawia iterator, żeby wskazywał na połączenie podane w argumencie.
       it.begin(); // ustawia na połączenie nr 0, równoważne z it[0], z tą różnicą, że nic nie zwraca
       unsigned i = 0;

       while(true) {
           if(i < server.connections()) {
               std::cout << "Liczba połączeń: " << (i = server.connections());
               it.end(); //wskazuje na ostatnie połączenie w tablicy, wynika to z faktu, że nowe połączenia są umieszczane na końcu tablicy
               (*it)->write("Witaj");
               std::string ans = (*it)->read();
               std::cout << " odpowiedź z " << (*it)->ipAdress() << " : " << ans << std::endl;

               if (ans == "CLOSE") {
                   it.close(); //zamyka (usuwa) połączenie
                   --i;

                   if(server.connections() == 0) {
                       server.stop();
                       break;
                   }
               }
           }

       }
    */
//Przykłady///////////////////////
    char input=-1;
    do {
        std::cin >> input;
        
    } while(input != 'q');
    return 0;
}
