//①出现error是因为存日志的目录或者文件不存在，所以报错
//②绑定Unix地址也是有问题的(应该是Unix路径不存在)
#include"../yancy_server/application.h"

int main(int argc,char** argv)
{
    yancy::Application app;
    if(app.init(argc,argv))
    {
        return app.run();
    }
    return 0;
}