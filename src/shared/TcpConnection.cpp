#include "TcpConnection.hpp"
#include "Packet.hpp"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include "server/Server.hpp"

TcpPointer TcpConnection::create(boost::asio::io_service &io_service) {
    return TcpPointer(new TcpConnection(io_service));
}

tcp::socket &TcpConnection::socket() {
    return socket_;
}
void TcpConnection::write(std::string message) {


    async_write(socket_, boost::asio::buffer(message),
                boost::bind(&TcpConnection::handle_write,
                            shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
}
void TcpConnection::wait_data() {
    async_read(socket_, response_,
               boost::bind(&TcpConnection::handle_read, this,
                           placeholders::error, placeholders::bytes_transferred));
}
void TcpConnection::close() {
    this->socket_.close();
}
std::string TcpConnection::ip_address() const {
    return this->socket_.remote_endpoint().address().to_string();
}

TcpConnection::TcpConnection(boost::asio::io_service &io_service)
    : socket_(io_service) {
}

void TcpConnection::handle_write(const boost::system::error_code & /*err*/,
                                 size_t /*size*/) {

}

void TcpConnection::handle_read(const boost::system::error_code &err,
                                size_t /*size*/) {
    if(!err) {
        Packet packet;
        std::istream is(&response_);
        boost::archive::text_iarchive ia(is); //jak go zaadresować?
        try {
            ia >> packet;
//	TcpServer::pointer->received.push(packet);

        }
        catch(std::exception ex) // to nie moze tak zostac, trzeba poinformowac jesli zlapiesz wyjatek
        {

            std::cerr << "Błąd serializacji pakietu";
        }
        wait_data();
    }
}
unsigned short TcpConnection::port() const {
    return this->socket_.remote_endpoint().port();

}
