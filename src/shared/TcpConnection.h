#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#define MAX_SIZE_MSG 1024
using boost::asio::ip::tcp;
using namespace boost::asio;

class tcpConnection : public boost::enable_shared_from_this<tcpConnection> {
  public:
    typedef boost::shared_ptr<tcpConnection> pointer;
    static pointer create(boost::asio::io_service &);
    tcp::socket &socket();
    void write();
    void read();
    std::string message;
    char response[MAX_SIZE_MSG];
    void close();
    std::string ipAdress();
  private:
    tcp::socket socket_;
    size_t size_;
    tcpConnection(boost::asio::io_service &);
    void handleWrite(const boost::system::error_code & /*error*/,
                     size_t /*bytes_transferred*/);
    void handleRead(const boost::system::error_code & /*error*/,
                    size_t /*bytes_transferred*/) ;
};
