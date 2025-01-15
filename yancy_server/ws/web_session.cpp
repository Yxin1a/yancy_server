#include "web_session.h"

namespace yancy
{
    namespace ws
    {
        std::string WSFrameHead::toString() const
        {
            std::stringstream ss;
            ss  << "[ WSFrameHead fin="<<fin
                << " opcode="<<opcode
                << " rsv3="<<rsv3
                << " rsv2="<<rsv2
                << " rsv1="<<rsv1
                << " payload="<<payload
                << " mask="<<mask;
            return ss.str();
        }

        WebMessage::WebMessage(int frame_head,const std::string& msg)
            : m_frame_head(frame_head)
            , m_msg(msg)
        {}

        yancy::http::HttpRequest::ptr WebSession::handleShake()
        {

        }
        WebMessage::ptr WebSession::recvMessage()
        {
            return WSRecvMessage(this,true);
        }
        int32_t WebSession::sendMessage(WebMessage::ptr web_message,bool fin)
        {
            return WSSendMessage(this,web_message,true,fin);
        }
        int32_t WebSession::sendMessage(const std::string& msg,int32_t frame_head,bool fin)
        {
            return WSSendMessage(this,std::make_shared<WebMessage>(frame_head,msg),true,fin);
        }
        
        int32_t WebSession::ping()
        {
            return WSPing(this);
        }
        int32_t WebSession::pong()
        {
            return WSPong(this);
        }

        WebMessage::ptr WSRecvMessage(Stream* stream, bool client)
        {
            
        }
        int32_t WSSendMessage(Stream* stream, WebMessage::ptr msg, bool client, bool fin)
        {

        }
        int32_t WSPing(Stream* stream)
        {
            WSFrameHead ws_head;
            memset(&ws_head, 0, sizeof(ws_head));
            ws_head.fin = 1;
            ws_head.opcode = WSFrameHead::PING;
            int32_t v = stream->writeFixSize(&ws_head, sizeof(ws_head));
            if(v <= 0) {
                stream->close();
            }
            return v;
        }
        int32_t WSPong(Stream* stream)
        {
            WSFrameHead ws_head;
            memset(&ws_head, 0 ,sizeof(ws_head));
            ws_head.fin = 1;
            ws_head.opcode = WSFrameHead::PONG;
            int32_t v = stream->writeFixSize(&ws_head,sizeof(ws_head));
            if(v<=0)
            {
                stream->close();
            }
            return v;
        }
        
    }
}