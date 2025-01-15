#ifndef __WEB_SERVLET_H__
#define __WEB_SERVLET_H__

#include <memory>
#include <string>

#include "yancy_server/http/servlet.h"
#include "web_session.h"

namespace yancy
{
    namespace ws
    {
        class WebServlet : public yancy::http::Servlet
        {
        public:
            typedef std::shared_ptr<WebServlet> ptr;

            WebServlet(const std::string& name);

            virtual ~WebServlet();

            virtual int32_t handle(yancy::http::HttpRequest::ptr request
                        , yancy::http::HttpResponse::ptr response
                        , yancy::http::HttpSession::ptr session) override
            {
                return 0;
            }

            virtual int32_t onopen (yancy::http::HttpRequest::ptr request
                        , yancy::ws::WebSession::ptr session) =0;
            // virtual int32_t onmessage(yancy::http::HttpRequest::ptr request
            //             , yancy::ws::WebSession::ptr session) =0;
            virtual int32_t handle(yancy::http::HttpRequest::ptr request
                        , yancy::ws::WebMessage::ptr msg
                        , yancy::ws::WebSession::ptr session) =0;
            virtual int32_t onclose(yancy::ws::WebSession::ptr session) =0;
            
            const std::string& getName() { return m_name; }

        private:
            std::string m_name;
        };

        /**
         * @brief 
         */
        class WebServletDispatch : public yancy::http::Servlet
        {
        public:
            std::shared_ptr<WebServletDispatch> ptr;

        private:

        };
    }
}

#endif