#include "TcpConnection.h"
namespace server {
TcpConnection::pointer TcpConnection::create(boost::asio::io_service &io_service) {
    return pointer(new TcpConnection(io_service));
}

tcp::socket &TcpConnection::socket() {
    return socket_;
}
void TcpConnection::write(std::string message) {


    boost::asio::async_write(socket_, boost::asio::buffer(message),
                             boost::bind(&TcpConnection::handleWrite,
                                         shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}
void TcpConnection::waitData() {
    async_read(socket_,  boost::asio::buffer(response_, size_),
               boost::bind(&TcpConnection::handleRead, this,
                           placeholders::error, placeholders::bytes_transferred));
}
void TcpConnection::close() {
    this->socket_.close();
}
std::string TcpConnection::ipAdress() {
    return this->socket_.remote_endpoint().address().to_string();
}

TcpConnection::TcpConnection(boost::asio::io_service &io_service)
    : socket_(io_service) {
    size_ = MAX_SIZE_MSG;
}

void TcpConnection::handleWrite(const boost::system::error_code &err,
                                size_t size) {

}

void TcpConnection::handleRead(const boost::system::error_code &err,
                               size_t size) {
    if(!err)
        waitData();

}
std::string TcpConnection::read() {
    mtx_.lock();
    std::string tmp (response_);
    std::memset(response_, ' ', sizeof(response_));
    mtx_.unlock();
    return tmp;
}
}
