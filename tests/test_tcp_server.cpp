#include"../yancy_server/tcp_server.h"

yancy::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run()
{
    //两台服务器监听
    auto addr = yancy::Address::LookupAny("0.0.0.0:8033");  //通过host地址返回对应条件的任意Address(服务器)
    //auto addr2 = yancy::UnixAddress::ptr(new yancy::UnixAddress("/tmp/unix_addr")); //通过路径构造UnixAddress(服务器)
    std::vector<yancy::Address::ptr> addrs;
    addrs.push_back(addr);
    //addrs.push_back(addr2);

    yancy::TcpServer::ptr tcp_server(new yancy::TcpServer);
    std::vector<yancy::Address::ptr> fails; //绑定失败的地址
    while(!tcp_server->bind(addrs, fails))
    {
        sleep(2);
    }
    tcp_server->start();    //开启服务器，进行监听和连接，数据处理
}

int main(int argc,char** argv)
{
    yancy::IOManager iom(2);    //分配2条线程给该协程调度器
    iom.schedule(run);
    return 0;
}