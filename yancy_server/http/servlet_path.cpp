#include"servlet_path.h"
#include"../log.h"

namespace yancy
{
    namespace http
    {
        
        static yancy::Logger::ptr g_logger=YANCY_LOG_NAME("system");

        //ServletPath
        ServletPath::ServletPath(ServletPathConf conf) //初始化
            :m_conf(conf)
        {}

        //ServletPathHtml
        ServletPathHtml::ServletPathHtml(ServletPathConf conf) //初始化
            :ServletPath(conf)
        {}

        static bool FileIfream(std::stringstream &ss,std::string path)  //读取path路径文件的数据到ss中··
        {
            std::ifstream ifs;
            ifs.open(path,std::ios::in);
            if(!ifs)
            {
                YANCY_LOG_INFO(g_logger)<<path<<" html file is exist";
                return false;
            }
            std::string buf;
            while(getline(ifs,buf))
            {
                ss<<buf;
            }
            return true;
        }

        bool ServletPathHtml::fun(yancy::http::ServletDispatch::ptr& dispatch)  //定义servlet匹配的回调函数
        {
            if(m_conf.type!="html")
            {
                YANCY_LOG_ERROR(g_logger)<<"servlet type error";
                return false;
            }
            dispatch->addServlet(m_conf.uri,[](yancy::http::HttpRequest::ptr req    //添加精准匹配servlet(回调函数)
                    ,yancy::http::HttpResponse::ptr rsp
                    ,yancy::http::HttpSession::ptr session)
            {
                YANCY_LOG_INFO(g_logger) << "请求" <<req->getPath()<<"的html类型文件";
                std::string path="/home/tq/桌面/yancy"+req->getPath()+".html";
                // std::string path=req->getPath()+".html";
                std::stringstream ss;
                if(!FileIfream(ss,path))
                {
                    YANCY_LOG_ERROR(g_logger) << "请求" <<req->getPath()<<"文件获取失败";
                    return false;
                }
                rsp->setBody(ss.str());
            });
            return true;
        }

    }
}