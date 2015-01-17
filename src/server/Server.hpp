#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <deque>
#include <boost/noncopyable.hpp>
#include "ClientsRegister.hpp"
#include "ClientDataRaw.hpp"
#include "shared/typedefinitions.hpp"
#include "Address.hpp"
using boost::asio::ip::tcp;
using namespace boost::asio;

class TcpServer : boost::noncopyable, ClientsRegister {
  public:
    void start();
    static TcpServer &getInstance(boost::asio::io_service &);
    void stop() {
        io_.stop();
    }
    unsigned connections();
  private:
    TcpServer(boost::asio::io_service &);
    void startAccept();
    void handleAccept(TcpPointer,
                      const boost::system::error_code &);
    tcp::acceptor acceptor_;
    boost::asio::io_service &io_;
};

