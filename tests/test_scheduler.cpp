#include"../yancy_server/yancy_server.h"

yancy::Logger::ptr g_logger=YANCY_LOG_ROOT();

void test_fiber()
{
    static int s_count=5;   //只用定义一次就行（多定义=第一次定义）

    YANCY_LOG_INFO(g_logger)<<"test in fiber s_count="<<s_count;

    sleep(1);
    if(--s_count>=0)
    {
        yancy::Scheduler::GetThis()->schedule(&test_fiber,yancy::GetThreadId()); //test_fiber存的是test_fiber函数指针
    }
}

int main(int argc,char** argv)
{
    YANCY_LOG_INFO(g_logger)<<"main";
    yancy::Scheduler sc(3,false,"test");
    sc.start();
    sleep(2);
    YANCY_LOG_INFO(g_logger)<<"schedule";
    sc.schedule(&test_fiber);   //协程队列插入
    sc.stop();
    YANCY_LOG_INFO(g_logger)<<"over";
    return 0;
}