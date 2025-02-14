#include "http_server.h"
#include "../log.h"
#include "../config.h"
#include "servlet_path.h"
#include "../env.h"
// #include "servlets/config_servlet.h"
// #include "servlets/status_servlet.h"

namespace yancy
{
    namespace http
    {

        static yancy::Logger::ptr g_logger = YANCY_LOG_NAME("system");

        static yancy::ConfigVar<std::vector<yancy::ServletPathConf>>::ptr g_servlet_conf
            = yancy::Config::Lookup("servlets", std::vector<yancy::ServletPathConf>(), "servlet path conf");

        HttpServer::HttpServer(bool keepalive   //构造函数(利用子类构造来初始化父类的变量)
                    ,yancy::IOManager* worker
                    ,yancy::IOManager* io_worker
                    ,yancy::IOManager* accept_worker)
            :TcpServer(worker, io_worker, accept_worker)
            ,m_isKeepalive(keepalive)
        {
            m_dispatch.reset(new ServletDispatch);

            std::string conf_path = yancy::EnvMgr::GetInstance()->getConfigPath();  //获取配置文件的绝对路径
            yancy::Config::LoadFromConfDir(conf_path);  //加载path文件夹里面的配置文件(如果配置文件没有变化，则不用加载该文件)

            //添加servlet匹配参数
            auto servlet_conf=g_servlet_conf->getValue();
            for(auto& i : servlet_conf)
            {
                yancy::http::ServletPath::ptr dispatch;
                if(i.type=="html")  //是html文件
                {
                    dispatch.reset(new yancy::http::ServletPathHtml(i));
                }
                if(!dispatch->fun(m_dispatch))
                {
                    YANCY_LOG_ERROR(g_logger)<<"servlet conf error";
                    break;
                }
            }

            // m_type = "http";
            // m_dispatch->addServlet("/_/status", Servlet::ptr(new StatusServlet));
            // m_dispatch->addServlet("/_/config", Servlet::ptr(new ConfigServlet));
        }

        void HttpServer::setName(const std::string& v)
        {
            TcpServer::setName(v);
            m_dispatch->setDefault(std::make_shared<NotFoundServlet>(v));
        }

        void HttpServer::handleClient(Socket::ptr client)   //处理新连接的Socket类(处理新连接的客户端数据传输)
        {
            YANCY_LOG_DEBUG(g_logger) << "handleClient " << *client;
            HttpSession::ptr session(new HttpSession(client));
            do {
                auto req = session->recvRequest();  //接收HTTP请求，并解析HTTP协议请求
                if(!req)
                {
                    YANCY_LOG_DEBUG(g_logger) << "recv http request fail, errno="
                        << errno << " errstr=" << strerror(errno)
                        << " cliet:" << *client << " keep_alive=" << m_isKeepalive;
                    break;
                }

                HttpResponse::ptr rsp(new HttpResponse(req->getVersion()
                                    ,req->isClose() || !m_isKeepalive));
                // rsp->setHeader("Server", getName());
                m_dispatch->handle(req, rsp, session);  //处理请求(决定具体请求哪个Servlet)
                session->sendResponse(rsp);

                if(!m_isKeepalive || req->isClose())
                {
                    break;
                }
            } while(true);
            session->close();
        }

    }
}
