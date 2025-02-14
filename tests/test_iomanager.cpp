#include"../yancy_server/yancy_server.h"
#include"../yancy_server/iomanager.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<iostream>

yancy::Logger::ptr g_logger=YANCY_LOG_ROOT();

int sock=0;

void test_fiber()
{
    YANCY_LOG_INFO(g_logger)<<"test_fiber sock="<<sock;
    
    //socket
    sock=socket(AF_INET,SOCK_STREAM,0); //创建socket
    fcntl(sock,F_SETFL,O_NONBLOCK);

    sockaddr_in addr;
    memset(&addr,0,sizeof(addr));   //清零————将addr中当前位置后面的sizeof(addr)个字节用0替换并返回addr
    addr.sin_family=AF_INET;
    addr.sin_port=htons(80);
    inet_pton(AF_INET,"120.232.145.185",&addr.sin_addr.s_addr); //将点分文本的IP地址转换为二进制网络字节序”的IP地址
    
    if(!connect(sock,(const sockaddr*)&addr,sizeof(addr)))  //套接字与指定的IP地址绑定====>bind
    {}
    else if(errno==EINPROGRESS)     //绑定失败
    {
        YANCY_LOG_INFO(g_logger)<<"add event errno="<<errno<<" "<<strerror(errno);

        yancy::IOManager::GetThis()->addEvent(sock,yancy::IOManager::READ,[]()
        {
            YANCY_LOG_INFO(g_logger)<<"read callback";
        });
        yancy::IOManager::GetThis()->addEvent(sock,yancy::IOManager::WRITE,[]() 
        {
            YANCY_LOG_INFO(g_logger)<<"write callback";
            yancy::IOManager::GetThis()->cancelEvent(sock,yancy::IOManager::READ);
            close(sock);
        });
    }
    else
    {
        YANCY_LOG_INFO(g_logger)<<"else "<<errno<<" "<<strerror(errno);
    }
}

void test1()    //没加定时器
{
    std::cout<<"EPOLLIN="<<EPOLLIN
             <<" EPOLLOUT="<<EPOLLOUT<<std::endl;
    yancy::IOManager iom(2,false);
    iom.schedule(&test_fiber);
}

yancy::Timer::ptr s_timer;
void test_timer()   //加定时器
{
    yancy::IOManager iom(2);
    iom.schedule(&test_fiber);
    s_timer=iom.addTimer(1000,[](){
        static int i=0;
        YANCY_LOG_INFO(g_logger)<<"hello timer i="<<i;    //[实参](){YANCY_LOG_INFO(g_logger)<<"hello timer";}是function<void ()>对应的实参
        if(++i==3)
        {
            s_timer->reset(2000,true);
            //s_timer->cancal();
        }
    },true);
}

int main(int argc,char** argv)
{
    //test1();
    test_timer();
    return 0;
}