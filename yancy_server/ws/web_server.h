#ifndef __WEB_SERVER_H__
#define __WEB_SERVER_H__

#include <memory>
#include <string>
#include "yancy_server/tcp_server.h"
#include "web_servlet.h"
#include "web_session.h"

namespace yancy
{
    namespace ws
    {
        class WebServer : public TcpServer
        {
        public:
            std::shared_ptr<WebServer> ptr;

            WebServer(yancy::IOManager* worker = yancy::IOManager::GetThis()
                    ,yancy::IOManager* io_worker = yancy::IOManager::GetThis()
                    ,yancy::IOManager* accept_worker = yancy::IOManager::GetThis());

            virtual void setName(const std::string& v) override;    //设置服务器名称

            WebServletDispatch::ptr getDispatch() const { return m_dispatch; }

            void setDispatch(const WebServletDispatch::ptr v) { m_dispatch = v; }

        protected:
        
            void handleClient(Socket::ptr client) override;  //处理新连接的Socket类(处理新连接的客户端数据传输)

        private:
            /// 服务器名称
            std::string m_name;
            /// 分发类管理器
            WebServletDispatch::ptr m_dispatch;
        };
    }
    
}

#endif