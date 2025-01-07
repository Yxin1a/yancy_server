#include"../yancy_server/yancy_server.h"

yancy::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void test_assert()
{
    SYLAR_LOG_INFO(g_logger)<<yancy::BacktraceToString(10);
    //SYLAR_ASSERT(false);
    SYLAR_ASSERT2(0==1,"abcdef xx");
}

int main(int argc,char** argv)
{
    test_assert();
    return 0;
}