#include "Logger.h"

Logger::Logger() : main(log4cpp::Category::getRoot()), debug(log4cpp::Category::getInstance(std::string("dbg")))
{
    console_appender = new log4cpp::OstreamAppender("console", &std::cout);
    console_appender->setLayout(simple_layout);
    log_appender = new log4cpp::FileAppender("logged", LOGFILE);
    log_appender->setLayout(detailed_layout);
    detailed_layout = new log4cpp::PatternLayout;
    simple_layout = new log4cpp::PatternLayout;

    detailed_layout->setConversionPattern(std::string("%-6p %-21d{%d.%m.%y;%H:%M:%S:%l} [%t]: %m%n"));
    simple_layout->setConversionPattern(std::string("%-6p %-5d{%r}: %m%n"));

    main.setPriority(log4cpp::Priority::INFO);
    main.addAppender(log_appender);
    main.addAppender(console_appender);

    debug.setPriority(log4cpp::Priority::DEBUG);
    debug.addAppender(console_appender);
}
