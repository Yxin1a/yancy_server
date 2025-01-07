#ifndef __SYLAR_HTTP_SERVLETS_CONFIG_SERVLET_H__
#define __SYLAR_HTTP_SERVLETS_CONFIG_SERVLET_H__

#include "../servlet.h"

namespace yancy {
namespace http {

class ConfigServlet : public Servlet {
public:
    ConfigServlet();
    virtual int32_t handle(yancy::http::HttpRequest::ptr request
                   , yancy::http::HttpResponse::ptr response
                   , yancy::http::HttpSession::ptr session) override;
};

}
}

#endif
