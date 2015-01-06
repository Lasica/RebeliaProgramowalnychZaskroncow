
#include "Server.h"
#define PORT 8001
namespace server {
TcpServer::TcpServer(boost::asio::io_service &io_service)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), PORT)), io_(io_service) {
}

void TcpServer::startAccept() {
    mtx_.lock();
    connections_.push_back(TcpConnection::create(acceptor_.get_io_service()));
    mtx_.unlock();
    acceptor_.async_accept(connections_.back()->socket(),
                           boost::bind(&TcpServer::handleAccept, this,
                                       boost::asio::placeholders::error));
}

void TcpServer::handleAccept( const boost::system::error_code &error) {
    if (!error)
        connections_.back()->waitData();

    mtx_.lock();
    connections_.push_back(TcpConnection::create(acceptor_.get_io_service()));
    mtx_.unlock();
    acceptor_.async_accept(connections_.back()->socket(),
                           boost::bind(&TcpServer::handleAccept, this,
                                       boost::asio::placeholders::error));

}
void TcpServer::start() {
    startAccept();
    boost::thread bt(boost::bind(&boost::asio::io_service::run, &io_));

}
TcpServer &TcpServer::getInstance(boost::asio::io_service &io) {
    static TcpServer serv(io);
    return serv;
}
TcpServer::ConIter TcpServer::getConIter() {
    ConIter it(connections_, &mtx_);
    return it;
}

unsigned TcpServer::connections() {
    return connections_.size() - 1;
}
}
