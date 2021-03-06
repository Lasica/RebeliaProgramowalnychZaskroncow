#include "server/Server.hpp"



#include "shared/TcpConnection.hpp"

TcpServer* TcpServer::pointer;


TcpServer::TcpServer(boost::asio::io_service &io_service)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), PORT)), io_(io_service), self_(nullptr) {
    //init();
}

void TcpServer::startAccept() {
    TcpPointer new_connection = TcpConnection::create(acceptor_.get_io_service());
    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&TcpServer::handleAccept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void TcpServer::handleAccept(TcpPointer new_connection_catched,
                             const boost::system::error_code &error) {
    if (!error) {
        Address add;
        add.ip = new_connection_catched->ip_address();
        add.port = new_connection_catched->port();
        add.update_connection(new_connection_catched);
        /*const Address *ptr = */registeredAddresses.register_address(add);
//        connectedClients.register_client(ptr, new_connection_catched);
        std::cout << "Registered connection at address: " << add.ip << ":" << add.port << std::endl;
        new_connection_catched->wait_data();
    }

    TcpPointer new_connection = TcpConnection::create(acceptor_.get_io_service());

    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&TcpServer::handleAccept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void TcpServer::start() {
    running_ = true;
    startAccept();

    init();
    self_ = new std::thread(boost::bind(&boost::asio::io_service::run, &io_));

}
TcpServer &TcpServer::getInstance() {
    static boost::asio::io_service io;
    static TcpServer serv(io);
    TcpServer::pointer = &serv;
    return serv;
}




