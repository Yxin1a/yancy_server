#include"../yancy_server/yancy_server.h"

yancy::Logger::ptr g_logger=YANCY_LOG_ROOT();

int count=0;    //公共数据
//yancy::RWMutex s_mutex; //读写互斥量
yancy::Mutex s_mutex; //互斥量

std::string path = std::getenv("PWD");

void fun1()
{
    YANCY_LOG_INFO(g_logger)<<"name: "<<yancy::Thread::GetName()
                            <<" this.name: "<<yancy::Thread::GetThis()->getName()
                            <<" id: "<<yancy::GetThreadId()
                            <<" this.id: "<<yancy::Thread::GetThis()->getId();
    for(int i=0;i<10000;++i)
    {
        //yancy::RWMutex::WriteLock lock(s_mutex);    //加写锁，超出作用域的加锁————lock是对象
        yancy::Mutex::Lock lock(s_mutex);    //加写锁，超出作用域的加锁 ————lock是对象
        
        ++count;
    }
}

void fun2()
{
    while(true)
    {
        YANCY_LOG_INFO(g_logger)<<"*************************";
    }
}

void fun3()
{
    while (true)
    {
        YANCY_LOG_INFO(g_logger)<<"=========================";
    }
}

int main(int argc,char** argv)
{
    YANCY_LOG_INFO(g_logger)<<"thread test begin";

    YAML::Node root=YAML::LoadFile(path+"/conf/log2.yml");  //LoadFile（）将yaml文件生成Node形式
    yancy::Config::LoadFromYaml(root);

    std::vector<yancy::Thread::ptr> thrs;
    for(int i=0;i<2;++i)   //创建2个线程
    {
        yancy::Thread::ptr thr(new yancy::Thread(&fun2,"name_"+std::to_string(i*2)));     //cb函数指针指向 fun1函数   to_string将整数i转换为字符串表示形式
        yancy::Thread::ptr thr2(new yancy::Thread(&fun3,"name_"+std::to_string(i*2+1)));     //cb函数指针指向 fun1函数   to_string将整数i转换为字符串表示形式
        thrs.push_back(thr);
        thrs.push_back(thr2);
    }

    
    for(size_t i=0;i<thrs.size();++i)
    {
        thrs[i]->join();    //等待子线程执行完
    }
    YANCY_LOG_INFO(g_logger)<<"thread test end";
    YANCY_LOG_INFO(g_logger)<<"count= "<<count;

    return 0;
}