#include <iostream>
#include "topson/log.h"
#include "topson/util.h"

int main(int argc, char** argv) {
    topson::Logger::ptr logger(new topson::Logger());
    logger->addAppender(topson::LogAppender::ptr(new topson::StdoutLogAppender()));

    topson::FileLogAppender::ptr file_appender(new topson::FileLogAppender("./log.txt"));
    topson::LogFormatter::ptr fmt(new topson::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(topson::LogLevel::ERROR);

    logger->addAppender(file_appender);

    //topson::LogEvent::ptr event(new topson::LogEvent(__FILE__, __LINE__, 0, topson::GetThreadId(), topson::GetFiberId(), time(0)));
    //event->getSS() << "hello topson log";
    //logger->log(topson::LogLevel::DEBUG, event);
    std::cout << "hello topson log" << std::endl;
    
    TOPSON_LOG_INFO(logger) << "test marco";
    TOPSON_LOG_ERROR(logger) << "test marco";

    TOPSON_LOG_FMT_ERROR(logger, "test marco fmt error %s", "aa");

    auto l = topson::LoggerMgr::GetInstance()->getLogger("xx");
    TOPSON_LOG_INFO(l) << "xxx";
    return 0;
}
