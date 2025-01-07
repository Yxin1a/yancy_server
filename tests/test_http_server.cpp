#include "../yancy_server/http/http_server.h"
#include "../yancy_server/log.h"

static yancy::Logger::ptr g_logger = SYLAR_LOG_ROOT();

#define XX(...) #__VA_ARGS__


yancy::IOManager::ptr worker;

void run()
{
    g_logger->setLevel(yancy::LogLevel::INFO);  //设置日志级别
    //yancy::http::HttpServer::ptr server(new yancy::http::HttpServer(true, worker.get(), yancy::IOManager::GetThis()));
    yancy::http::HttpServer::ptr server(new yancy::http::HttpServer); //创建HTTP服务器
    yancy::Address::ptr addr = yancy::Address::LookupAnyIPAddress("0.0.0.0:8020");  //通过host地址返回对应条件的任意IPAddress
    while(!server->bind(addr))  //绑定地址
    {
        sleep(2);
    }
    auto sd = server->getServletDispatch(); //获取ServletDispatch(管理类) 
    sd->addServlet("/yancy/xx", [](yancy::http::HttpRequest::ptr req    //添加精准匹配servlet(回调函数)
                ,yancy::http::HttpResponse::ptr rsp
                ,yancy::http::HttpSession::ptr session) {
            rsp->setBody(req->toString());
            return 0;
    });

    sd->addGlobServlet("/yancy/*", [](yancy::http::HttpRequest::ptr req //添加模糊匹配servlet(回调函数)
                ,yancy::http::HttpResponse::ptr rsp
                ,yancy::http::HttpSession::ptr session) {
            rsp->setBody("Glob:\r\n" + req->toString());
            return 0;
    });

    sd->addGlobServlet("/yancyx/*", [](yancy::http::HttpRequest::ptr req
                ,yancy::http::HttpResponse::ptr rsp
                ,yancy::http::HttpSession::ptr session) {
            rsp->setBody(XX(<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.16.0</center>
</body>
</html>
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
));
            return 0;
    });

    server->start();
}

int main(int argc, char** argv)
{
    yancy::IOManager iom(2);
    // yancy::IOManager iom(1, true, "main");
    // worker.reset(new yancy::IOManager(3, false, "worker"));
    iom.schedule(run);
    
    return 0;
}
