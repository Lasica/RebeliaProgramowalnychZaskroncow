#ifndef LOGGER_H
#define LOGGER_H
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/PatternLayout.hh"
#include "log4cpp/Priority.hh"

#define LOGFILE "server.log"

class Logger
{
public:
    log4cpp::Category       &main;
    log4cpp::Category       &debug;
    static Logger& getInstance() {
        static Logger x;
        return x;
    }
    static log4cpp::CategoryStream log_debug()   {
        return getInstance().debug.debugStream();
    }
    static log4cpp::CategoryStream log_main()    {
        return getInstance().main.infoStream();
    }
private:
    Logger();
    Logger(const Logger&) = delete;
    log4cpp::Appender       *console_appender;
    log4cpp::Appender       *log_appender;
    log4cpp::PatternLayout  *detailed_layout;
    log4cpp::PatternLayout  *simple_layout;
    /* examples
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
        root.errorStream() << "Another streamed error"; */
};

#endif // LOGGER_H
