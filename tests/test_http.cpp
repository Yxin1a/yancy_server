#include"../yancy_server/http/http.h"
#include"../yancy_server/log.h"

void test_request()
{
    yancy::http::HttpRequest::ptr req(new yancy::http::HttpRequest);
    req->setHeader("host","www.yancy.top");
    req->setBody("hello yancy");
    req->dump(std::cout)<<std::endl;
}

void test_response()
{
    yancy::http::HttpResponse::ptr rsp(new yancy::http::HttpResponse);
    rsp->setHeader("X-X","yancy");
    rsp->setStatus((yancy::http::HttpStatus)400);
    rsp->setClose(false);
    rsp->setBody("hello yancy");
    rsp->dump(std::cout)<<std::endl;
}

int main(int argc,char** argv)
{
    test_request();
    test_response();
    return 0;
}