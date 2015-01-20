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
//#include "server/ClientsRegister.hpp"
//#include "server/ClientDataRaw.hpp"
//#include "shared/typedefinitions.hpp"
#include "server/Address.hpp"
#include "server/ServerResources.hpp"
using boost::asio::ip::tcp;
using namespace boost::asio;

class TcpServer : boost::noncopyable, public ServerResources {
public:
    void start();
    static TcpServer &getInstance();
    void stop() {
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
