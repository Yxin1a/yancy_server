/**
 * @brief 服务器启动
 */

#include"application.h"

int main(int argc,char** argv)
{
    yancy::Application app;
    if(app.init(argc,argv))
    {
        return app.run();
    }
    return 0;
}