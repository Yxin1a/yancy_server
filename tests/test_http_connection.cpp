#include <iostream>
#include "yancy_server/http/http_connection.h"
#include "yancy_server/log.h"
#include "yancy_server/iomanager.h"
#include "yancy_server/http/http_parser.h"
//#include "yancy-master/streams/zlib_stream.h"
#include <fstream>

static yancy::Logger::ptr g_logger = YANCY_LOG_ROOT();

void test_pool()
{
    yancy::http::HttpConnectionPool::ptr pool(new yancy::http::HttpConnectionPool(
                "www.yancy.top", "", 80, false, 10, 1000 * 30, 5));

    yancy::IOManager::GetThis()->addTimer(1000, [pool](){
            auto r = pool->doGet("/", 300); //发送HTTP的GET请求(字符串uri)
            YANCY_LOG_INFO(g_logger) << r->toString();
    }, true);
}

void run()
{
    yancy::Address::ptr addr = yancy::Address::LookupAnyIPAddress("www.yancy.top:80");  //通过host地址返回对应条件的任意IPAddress
    if(!addr)
    {
        YANCY_LOG_INFO(g_logger) << "get addr error";
        return;
    }

    yancy::Socket::ptr sock = yancy::Socket::CreateTCP(addr);   //利用Address创建TCP Socket
    bool rt = sock->connect(addr);  //客户端连接服务器地址
    if(!rt)
    {
        YANCY_LOG_INFO(g_logger) << "connect " << *addr << " failed";
        return;
    }

    yancy::http::HttpConnection::ptr conn(new yancy::http::HttpConnection(sock));   //HTTP客户端类(处理客户端和服务器的交流)
    yancy::http::HttpRequest::ptr req(new yancy::http::HttpRequest);    //HTTP请求结构体
    req->setPath("/blog/"); //设置HTTP请求的路径
    req->setHeader("host", "www.yancy.top");    //设置HTTP请求的头部参数
    YANCY_LOG_INFO(g_logger) << "req:" << std::endl
        << *req;

    conn->sendRequest(req); //发送HTTP请求
    auto rsp = conn->recvResponse();    //接收HTTP响应，解析响应协议

    if(!rsp)
    {
        YANCY_LOG_INFO(g_logger) << "recv response error";
        return;
    }
    YANCY_LOG_INFO(g_logger) << "rsp:" << std::endl
        << *rsp;

    std::ofstream ofs("rsp.dat");
    ofs << *rsp;

    YANCY_LOG_INFO(g_logger) << "=========================";

    auto r = yancy::http::HttpConnection::DoGet("http://www.yancy.top/blog/", 300); //发送HTTP的GET请求(字符串uri)
    YANCY_LOG_INFO(g_logger) << "result=" << r->result
        << " error=" << r->error
        << " rsp=" << (r->response ? r->response->toString() : "");

    YANCY_LOG_INFO(g_logger) << "=========================";
    test_pool();
}

// void test_https()
// {
//     auto r = yancy::http::HttpConnection::DoGet("http://www.baidu.com/", 300,{
//                         {"Accept-Encoding", "gzip, deflate, br"},
//                         {"Connection", "keep-alive"},
//                         {"User-Agent", "curl/7.29.0"}
//             });
//     YANCY_LOG_INFO(g_logger) << "result=" << r->result
//         << " error=" << r->error
//         << " rsp=" << (r->response ? r->response->toString() : "");

//     //yancy::http::HttpConnectionPool::ptr pool(new yancy::http::HttpConnectionPool(
//     //            "www.baidu.com", "", 80, false, 10, 1000 * 30, 5));
//     auto pool = yancy::http::HttpConnectionPool::Create(
//                     "https://www.baidu.com", "", 10, 1000 * 30, 5);
//     yancy::IOManager::GetThis()->addTimer(1000, [pool](){
//             auto r = pool->doGet("/", 3000, {
//                         {"Accept-Encoding", "gzip, deflate, br"},
//                         {"User-Agent", "curl/7.29.0"}
//                     });
//             YANCY_LOG_INFO(g_logger) << r->toString();
//     }, true);
// }

// void test_data()
// {
//     yancy::Address::ptr addr = yancy::Address::LookupAny("www.baidu.com:80");
//     auto sock = yancy::Socket::CreateTCP(addr);

//     sock->connect(addr);
//     const char buff[] = "GET / HTTP/1.1\r\n"
//                 "connection: close\r\n"
//                 "Accept-Encoding: gzip, deflate, br\r\n"
//                 "Host: www.baidu.com\r\n\r\n";
//     sock->send(buff, sizeof(buff));

//     std::string line;
//     line.resize(1024);

//     std::ofstream ofs("http.dat", std::ios::binary);
//     int total = 0;
//     int len = 0;
//     while((len = sock->recv(&line[0], line.size())) > 0)
//     {
//         total += len;
//         ofs.write(line.c_str(), len);
//     }
//     std::cout << "total: " << total << " tellp=" << ofs.tellp() << std::endl;
//     ofs.flush();
// }

// void test_parser()
// {
//     std::ifstream ifs("http.dat", std::ios::binary);
//     std::string content;
//     std::string line;
//     line.resize(1024);

//     int total = 0;
//     while(!ifs.eof())
//     {
//         ifs.read(&line[0], line.size());
//         content.append(&line[0], ifs.gcount());
//         total += ifs.gcount();
//     }

//     std::cout << "length: " << content.size() << " total: " << total << std::endl;
//     yancy::http::HttpResponseParser parser;
//     size_t nparse = parser.execute(&content[0], content.size(), false);
//     std::cout << "finish: " << parser.isFinished() << std::endl;
//     content.resize(content.size() - nparse);
//     std::cout << "rsp: " << *parser.getData() << std::endl;

//     auto& client_parser = parser.getParser();
//     std::string body;
//     int cl = 0;
//     do {
//         size_t nparse = parser.execute(&content[0], content.size(), true);
//         std::cout << "content_len: " << client_parser.content_len
//                   << " left: " << content.size()
//                   << std::endl;
//         cl += client_parser.content_len;
//         content.resize(content.size() - nparse);
//         body.append(content.c_str(), client_parser.content_len);
//         content = content.substr(client_parser.content_len + 2);
//     } while(!client_parser.chunks_done);

//     std::cout << "total: " << body.size() << " content:" << cl << std::endl;

//     yancy::ZlibStream::ptr stream = yancy::ZlibStream::CreateGzip(false);
//     stream->write(body.c_str(), body.size());
//     stream->flush();

//     body = stream->getResult();

//     std::ofstream ofs("http.txt");
//     ofs << body;
// }

int main(int argc, char** argv) 
{
    yancy::IOManager iom(2);
    iom.schedule(run);
    //iom.schedule(test_https);
    return 0;
}
