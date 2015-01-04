#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "shared/TcpConnection.h"
#include <deque>
using boost::asio::ip::tcp;
using namespace boost::asio;

class tcpConnection;
class tcpServer {
  public:
    std::deque<tcpConnection::pointer> connections;
    tcpServer(boost::asio::io_service &);
  private:
    void startAccept();
    void handleAccept(tcpConnection::pointer,
                      const boost::system::error_code &);
    tcp::acceptor acceptor_;
};
