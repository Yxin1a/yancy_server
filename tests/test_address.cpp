#include"../yancy_server/address.h"
#include"../yancy_server/log.h"

yancy::Logger::ptr g_logger=YANCY_LOG_ROOT();

void test() //测试域名
{
    std::vector<yancy::Address::ptr> addrs;

    YANCY_LOG_INFO(g_logger)<<"begin";
    bool v=yancy::Address::Lookup(addrs,"www.yancy.top");   //查看域名的address
    YANCY_LOG_INFO(g_logger)<<"end";
    if(!v)
    {
        YANCY_LOG_ERROR(g_logger)<<"lookup fail";
        return;
    }

    for(size_t i=0;i<addrs.size();++i)
    {
        YANCY_LOG_INFO(g_logger)<<i<<"-"<<addrs[i]->toString(); //返回可读性字符串
    }
}

void test_iface()   //测试网卡
{
    std::multimap<std::string,std::pair<yancy::Address::ptr,uint32_t>> results;

    bool v=yancy::Address::GetInterfaceAddresses(results);  //返回本机所有网卡的
    if(!v)
    {
        YANCY_LOG_ERROR(g_logger)<<"GetInterfaceAddresses fail";
        return;
    }

    for(auto& i:results)
    {
        YANCY_LOG_INFO(g_logger)<<i.first<<"-"<<i.second.first->toString()<<"-" //返回可读性字符串
            <<i.second.second;
    }
}

void test_ipv4()    //测试ipv4
{
    auto addr=yancy::IPAddress::Create("www.baidu.com");
    if(addr)
    {
        YANCY_LOG_INFO(g_logger)<<addr->toString();
    }
}

int main(int argc,char** argv)
{
    test_ipv4();
    test();
    test_iface();
    return 0;
}