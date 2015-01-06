#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread/mutex.hpp>

#define MAX_SIZE_MSG 1024
namespace server {
using boost::asio::ip::tcp;
using namespace boost::asio;

class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
  public:
    typedef boost::shared_ptr<TcpConnection> pointer;
    static pointer create(boost::asio::io_service &);
    tcp::socket &socket();
    void write(std::string);
    std::string read();
    std::string ipAdress();
    void waitData();
    ~TcpConnection() {
        close();
    }
  private:
    void close();
    boost::mutex mtx_;
    char response_[MAX_SIZE_MSG];
    tcp::socket socket_;
    size_t size_;
    TcpConnection(boost::asio::io_service &);
    void handleWrite(const boost::system::error_code & /*error*/,
                     size_t /*bytes_transferred*/);
    void handleRead(const boost::system::error_code & /*error*/,
                    size_t /*bytes_transferred*/) ;
};
}
