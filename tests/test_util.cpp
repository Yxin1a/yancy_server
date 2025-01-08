#include"../yancy_server/yancy_server.h"

yancy::Logger::ptr g_logger=YANCY_LOG_ROOT();

void test_assert()
{
    YANCY_LOG_INFO(g_logger)<<yancy::BacktraceToString(10);
    //YANCY_ASSERT(false);
    YANCY_ASSERT2(0==1,"abcdef xx");
}

int main(int argc,char** argv)
{
    test_assert();
    return 0;
}