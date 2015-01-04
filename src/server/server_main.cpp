#include "server/Server.h"
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"

#define LOGFILE "tmp/server.log"
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;
using namespace boost::asio;
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
        tcpServer server(io_service);
        io_service.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
