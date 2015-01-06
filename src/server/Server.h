#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "../shared/TcpConnection.h"
#include <boost/thread/thread.hpp>
#include <deque>
#include <boost/noncopyable.hpp>
namespace server {
using boost::asio::ip::tcp;
using namespace boost::asio;

class TcpConnection;
class TcpServer : boost::noncopyable {
  public:
    class ConIter {
      public:
        ConIter(std::deque<server::TcpConnection::pointer> &con, boost::mutex *mtx): connections_(con), mtx_(mtx) {
            counter_ = 0;
        }
        TcpConnection::pointer operator*();
        TcpConnection::pointer operator[](int);
        ConIter &operator++();
        ConIter &operator--();
        ConIter operator+(int);
        ConIter operator-(int);
        bool operator==(ConIter &);
        bool operator!=(ConIter &);
        ConIter &operator=(const ConIter &);
        void close();
        ConIter &begin();
        ConIter &end();
      private:
        std::deque<server::TcpConnection::pointer> &connections_;
        boost::mutex *mtx_;
        unsigned counter_;
    };
    void start();
    static TcpServer &getInstance(boost::asio::io_service &);
    void stop() {
        io_.stop();
    }
    ConIter getConIter();
    unsigned connections();
  private:
    std::deque<TcpConnection::pointer> connections_;
    TcpServer(boost::asio::io_service &);
    void startAccept();
    void handleAccept(
        const boost::system::error_code &);
    tcp::acceptor acceptor_;
    boost::asio::io_service &io_;
    boost::mutex mtx_;
};
}

