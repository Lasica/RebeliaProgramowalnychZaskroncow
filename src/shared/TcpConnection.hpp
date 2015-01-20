#ifndef TCP_CONNECTION
#define TCP_CONNECTION

#include <iostream>

#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>
#include "shared/typedefinitions.hpp"

using boost::asio::ip::tcp;
using namespace boost::asio;

class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
public:

    static TcpPointer create(boost::asio::io_service &);
    tcp::socket &socket();
    void write(std::string);
    std::string read() const;
    std::string ip_address() const;
    void wait_data();
    unsigned short port() const;
    ~TcpConnection() {
        close();
    }
private:
    void close();
    boost::mutex mtx_;
    streambuf response_;
    tcp::socket socket_;
    TcpConnection(boost::asio::io_service &);
    void handle_write(const boost::system::error_code & /*error*/,
                      size_t /*bytes_transferred*/);
    void handle_read(const boost::system::error_code & /*error*/,
                     size_t /*bytes_transferred*/) ;
};

#endif
