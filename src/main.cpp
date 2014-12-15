#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

#define LOGFILE "tmp/server.log"
#include <ctime> // FIXME: USE CHRONO OR DATETIME
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace boost::asio;

class tcp_connection
    : public boost::enable_shared_from_this<tcp_connection> {
  public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_service &io_service) {
        return pointer(new tcp_connection(io_service));
    }

    tcp::socket &socket() {
        return socket_;
    }

    //wyszystko pracuje w pętli, dlatego się nie rozłącza - ze start skacze do handler_write, z niego do start() itd. - tak było w przykładowym czacie
    //Dodatkowo w każdej iteracji odbierane są dane przez read()
    // message_ co ma wysłać
    // response_ co zostało odebrane (przy czym jest typu streambuf)
    void write() {
    message_ = socket_.remote_endpoint().address().to_string(); // wysyła adres IP do odbiorcy

    read();
        boost::asio::async_write(socket_, boost::asio::buffer(message_),
                                 boost::bind(&tcp_connection::handle_write,
                                             shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }
    void read(){
  async_read(socket_, response_,
                    boost::bind(&tcp_connection::handle_read, this,
                    placeholders::error, placeholders::bytes_transferred));
    }

  private:
    tcp_connection(boost::asio::io_service &io_service)
        : socket_(io_service) {
    }

    void handle_write(const boost::system::error_code & /*error*/,
                      size_t /*bytes_transferred*/) {
                        write();
    }
   void handle_read(const boost::system::error_code & /*error*/,
                      size_t /*bytes_transferred*/) {

    }

    tcp::socket socket_;
    std::string message_;
    boost::asio::streambuf response_;
};

class tcp_server {
  public:
    tcp_server(boost::asio::io_service &io_service)
        : acceptor_(io_service, tcp::endpoint(tcp::v4(), 13)) {
        start_accept();
    }

  private:
    void start_accept() {
        tcp_connection::pointer new_connection =
            tcp_connection::create(acceptor_.get_io_service());

        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&tcp_server::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection,
                       const boost::system::error_code &error) {
        if (!error)
            new_connection->write();

        start_accept();
    }

    tcp::acceptor acceptor_;
};



int main() {
log4cpp::Appender *console_appender = new log4cpp::OstreamAppender("console", &std::cout);
    console_appender->setLayout(new log4cpp::BasicLayout());

    log4cpp::Appender *log_appender = new log4cpp::FileAppender("default", LOGFILE);
    log_appender->setLayout(new log4cpp::BasicLayout());

    log4cpp::Category &root = log4cpp::Category::getRoot();
    root.setPriority(log4cpp::Priority::WARN);
    root.addAppender(console_appender);

    log4cpp::Category &sub1 = log4cpp::Category::getInstance(std::string("stored"));
    sub1.addAppender(log_appender);

    // use of functions for logging messages
    root.error("root error");
    root.info("root info");
    sub1.error("stored error");
    sub1.warn("stored warn");

    // printf-style for logging variables
    root.warn("%d + %d == %s ?", 1, 1, "two");

    // use of streams for logging messages
    root << log4cpp::Priority::ERROR << "Streamed root error";
    root << log4cpp::Priority::INFO << "Streamed root info";
    sub1 << log4cpp::Priority::ERROR << "Streamed sub1 error";
    sub1 << log4cpp::Priority::WARN << "Streamed sub1 warn";

    // or this way:
    root.errorStream() << "Another streamed error";


    try {
        boost::asio::io_service io_service;
        tcp_server server(io_service);
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
