#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/noncopyable.hpp>
#include <deque>
#include <iostream>
#include <string>

#include "server/Address.hpp"
#include "server/ServerResources.hpp"
using boost::asio::ip::tcp;
using namespace boost::asio;

/*!
 *  Ta klasa pośredniczy w wymianie informacji pomiędzy tym, co znajduje się w ServerResources, a graczami podłączonymi przez internet.
 *  Jest singletonem i to jej instancja jest uruchamiana przy włączeniu programu.
 */


class TcpServer : boost::noncopyable, public ServerResources {
public:
    void start();           //! serwer zaczyna pracować po wywołaniu tej metody
    static TcpServer &getInstance();
    void stop()             //! metoda kończąca pracę serwera
    {
        io_.stop();
        running_ = false;
    }
    ~TcpServer() {
        if(self_ != nullptr) {
            if(self_->joinable())
                self_->join();
            delete self_;
        }
    }
    static TcpServer* pointer;
private:
    TcpServer(boost::asio::io_service &);
    void startAccept();
    void handleAccept(TcpPointer,
                      const boost::system::error_code &);
    tcp::acceptor acceptor_;
    boost::asio::io_service &io_;

    std::thread *self_;
};
#endif
