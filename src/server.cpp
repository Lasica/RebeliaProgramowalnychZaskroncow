
#include "server.h"

using boost::asio::ip::tcp;
using namespace boost::asio;
//namespace posix = boost::asio::posix;

    tcpServer::tcpServer(boost::asio::io_service &io_service)
        : acceptor_(io_service, tcp::endpoint(tcp::v4(), 13)) {
        startAccept();
    }

    void tcpServer::startAccept() {
        std::deque<tcpConnection::pointer>::iterator it;
        connections.push_back(tcpConnection::create(acceptor_.get_io_service()));
        it = connections.end();
        --it;
        acceptor_.async_accept((*it)->socket(),
                               boost::bind(&tcpServer::handleAccept, this, *it,
                                           boost::asio::placeholders::error));
        connections.erase(it);
    }

    void tcpServer::handleAccept(tcpConnection::pointer newConnection,
                       const boost::system::error_code &error) {
        if (!error)
        {
        //Prosty echoserver
        // przesyła z powrotem odebraną wiadomość od odbiorcy + ip odbiorcy
        // dostęp do wszystkich nawiązanych połączeń jest poprzez kolekcję connections typu deque
        // newConnection jest połączeniem które wywołało tą instancję uchwytu
        // czyli kiedy przychodzi nowe połączenie wykonywany jest poniższy kod
            newConnection->read();
            newConnection->message = newConnection->response;
            newConnection->message += newConnection->ipAdress();
            newConnection->write();
            newConnection->close();
        }
    }


