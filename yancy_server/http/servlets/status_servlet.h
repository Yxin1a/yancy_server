#ifndef __YANCY_HTTP_SERVLETS_STATUS_SERVLET_H__
#define __YANCY_HTTP_SERVLETS_STATUS_SERVLET_H__

#include "../servlet.h"

namespace yancy
{
    namespace http
    {

        class StatusServlet : public Servlet
        {
        public:

            StatusServlet();    //初始化

            virtual int32_t handle(yancy::http::HttpRequest::ptr request
                        , yancy::http::HttpResponse::ptr response
                        , yancy::http::HttpSession::ptr session) override;
        };

    }
}

#endif
