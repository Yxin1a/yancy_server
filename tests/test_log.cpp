#include<iostream>
#include"../yancy_server/log.h"
#include"../yancy_server/util.h"
using namespace std;


int main(int argc,char ** argv)
{
    yancy::Logger::ptr logger(new yancy::Logger);
    logger->addAppender(yancy::LogAppender::ptr(new yancy::StdoutLogAppender)); //给输出目标定义输出到控制台的目标

    yancy::FileLogAppender::ptr file_appender(new yancy::FileLogAppender("./log.txt"));
    yancy::LogFormatter::ptr fmt(new yancy::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);//将默认格式器的格式更改
    file_appender->setLevel(yancy::LogLevel::ERROR);

    logger->addAppender(file_appender);//给输出目标定义输出到log.txt文件的目标

    // yancy::LogEvent::ptr event(new yancy::LogEvent(__FILE__,__LINE__,0,yancy::GetThreadId(),yancy::GetFiberId(),time(0)));  //日志事件的数据
    // event->getSS()<<"hello yancy log";

    // logger->log(yancy::LogLevel::DEBUG,event);  //将数据给日志器
    std::cout<<"hello yancy log"<<std::endl;

    SYLAR_LOG_INFO(logger)<<"test macro";
    SYLAR_LOG_ERROR(logger)<<"test error";

    SYLAR_LOG_FMT_ERROR(logger,"test macro fmt error %s","aa");

    auto l=yancy::LoggerMgr::GetInstance()->getLogger("XX"); 
    SYLAR_LOG_INFO(l)<<"XXX";
    return 0;
}
