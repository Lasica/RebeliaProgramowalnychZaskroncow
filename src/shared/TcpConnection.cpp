#include "shared/TcpConnection.h"

tcpConnection::pointer tcpConnection::create(boost::asio::io_service &io_service) {
    return pointer(new tcpConnection(io_service));
}

tcp::socket &tcpConnection::socket() {
    return socket_;
}
void tcpConnection::write() {


    boost::asio::async_write(socket_, boost::asio::buffer(message),
                             boost::bind(&tcpConnection::handleWrite,
                                         shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}
void tcpConnection::read() {
    async_read(socket_,  boost::asio::buffer(response, size_),
               boost::bind(&tcpConnection::handleRead, this,
                           placeholders::error, placeholders::bytes_transferred));
}
void tcpConnection::close() {
    this->socket_.close();
}
std::string tcpConnection::ipAdress() {
    return this->socket_.remote_endpoint().address().to_string();
}

tcpConnection::tcpConnection(boost::asio::io_service &io_service)
    : socket_(io_service) {
    size_ = MAX_SIZE_MSG;
}

void tcpConnection::handleWrite(const boost::system::error_code & /*error*/,
                                size_t /*bytes_transferred*/) {

}

void tcpConnection::handleRead(const boost::system::error_code & /*error*/,
                               size_t /*bytes_transferred*/) {

}
