#include"../yancy_server/yancy_server.h"

yancy::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void run_in_fiber() //子协程函数
{
    SYLAR_LOG_INFO(g_logger)<<"run_in_fiber begin";
    yancy::Fiber::YieldToHold();    //将当前协程切换到后台,并设置为HOLD状态(切换到主协程)
    SYLAR_LOG_INFO(g_logger)<<"run_in_fiber end";
    yancy::Fiber::YieldToHold();    //将当前协程切换到后台,并设置为HOLD状态(切换到主协程)
}

void test_fiber()   //主协程函数
{
    SYLAR_LOG_INFO(g_logger)<<"main begin -1";
    {
        yancy::Fiber::GetThis();    //返回当前所在的协程,没有则创建新的主协程
        SYLAR_LOG_INFO(g_logger)<<"main begin";
        yancy::Fiber::ptr fiber(new yancy::Fiber(run_in_fiber));    //new创建子协程
        fiber->swapIn();    //将当前协程切换到运行状态，并将主协程切换到后台(切换到子协程)
        SYLAR_LOG_INFO(g_logger)<<"main after swapIn";
        fiber->swapIn();    //将当前协程切换到运行状态，并将主协程切换到后台(切换到子协程)
        SYLAR_LOG_INFO(g_logger)<<"main after end";
        fiber->swapIn();    //将当前协程切换到运行状态，并将主协程切换到后台(切换到子协程释放————手动)
    }
    SYLAR_LOG_INFO(g_logger)<<"main after end2";
}

int main(int argc,char** argv)
{
    yancy::Thread::SetName("main");
    
    std::vector<yancy::Thread::ptr> thrs;
    for(int i=0;i<3;++i)
    {
        thrs.push_back(yancy::Thread::ptr(new yancy::Thread(&test_fiber,"name_"+std::to_string(i))));   //创建线程
    }
    for(auto i : thrs)
    {
        i->join();
    }
    return 0;
}