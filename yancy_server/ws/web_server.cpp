#include "web_server.h"
#include "yancy_server/log.h"

namespace yancy
{
    namespace ws
    {
        static yancy::Logger::ptr g_logger = YANCY_LOG_NAME("system");

        WebServer::WebServer(yancy::IOManager* worker = yancy::IOManager::GetThis()
                ,yancy::IOManager* io_worker = yancy::IOManager::GetThis()
                ,yancy::IOManager* accept_worker = yancy::IOManager::GetThis())
            : TcpServer(worker,io_worker,accept_worker)
        {
            m_dispatch.reset(new WebServletDispatch());
        }

        void WebServer::setName(const std::string& v)    //设置服务器名称
        {
            TcpServer::setName(v);
        }

        void WebServer::handleClient(Socket::ptr client)  //处理新连接的Socket类(处理新连接的客户端数据传输)
        {
            YANCY_LOG_DEBUG(g_logger) << "webServer handleClient";
            
        }
    }
    
}