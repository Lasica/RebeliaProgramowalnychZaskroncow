#include "server/Server.h"
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

#define LOGFILE "tmp/server.log"
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
using namespace boost::asio;
int main() {
    log4cpp::Appender *console_appender = new log4cpp::OstreamAppender("console", &std::cout);
    console_appender->setLayout(new log4cpp::BasicLayout());

    log4cpp::Appender *log_appender = new log4cpp::FileAppender("default", LOGFILE);
    log_appender->setLayout(new log4cpp::BasicLayout());

    log4cpp::Category &root = log4cpp::Category::getRoot();
    root.setPriority(log4cpp::Priority::WARN);
    root.addAppender(console_appender);

    log4cpp::Category &sub1 = log4cpp::Category::getInstance(std::string("stored"));
    sub1.addAppender(log_appender);

    // use of functions for logging messages
    root.error("root error");
    root.info("root info");
    sub1.error("stored error");
    sub1.warn("stored warn");

    // printf-style for logging variables
    root.warn("%d + %d == %s ?", 1, 1, "two");

    // use of streams for logging messages
    root << log4cpp::Priority::ERROR << "Streamed root error";
    root << log4cpp::Priority::INFO << "Streamed root info";
    sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
    sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

    // or this way:
    root.errorStream() << "Another streamed error";

    io_service io;
    TcpServer &server = TcpServer::getInstance(io);
    server.start();
    std::cout << "Serwer uruchomiony" << std::endl;
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
    return 0;
}
