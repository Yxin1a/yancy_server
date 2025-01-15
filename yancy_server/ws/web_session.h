#ifndef __WEB_SESSION_H__
#define __WEB_SESSION_H__

#include <memory>
#include <string.h>
#include "yancy_server/http/http_session.h"
#include "yancy_server/streams/socket_stream.h"

namespace yancy
{
    namespace ws
    {

        #pragma pack(1)
        /**
         * @brief WS协议头部
         */
        struct WSFrameHead {
            enum OPCODE {
                /// 数据分片帧
                CONTINUE = 0,
                /// 文本帧
                TEXT_FRAME = 1,
                /// 二进制帧
                BIN_FRAME = 2,
                /// 断开连接
                CLOSE = 8,
                /// PING
                PING = 0x9,
                /// PONG
                PONG = 0xA
            };
            uint32_t opcode: 4;
            bool rsv3: 1;
            bool rsv2: 1;
            bool rsv1: 1;
            bool fin: 1;
            uint32_t payload: 7;
            bool mask: 1;

            std::string toString() const;
        };
        #pragma pack()

        /**
         * @brief 
         */
        class WebMessage
        {
        public:
            typedef std::shared_ptr<WebMessage> ptr;

            WebMessage(int frame_head = 0,const std::string& msg = "");

            int getFrameHead() const { return m_frame_head; }
            void setFrameHead(const int& v) { m_frame_head=v; }

            const std::string& getMsg() const { return m_msg; }
            void setMsg(const std::string& v) { m_msg=v; }
            std::string& getMsg() { return m_msg; }

        private:
            //WS协议头部
            int m_frame_head;
            //WS协议内容
            std::string m_msg;
        };

        /**
         * @brief websocket通道
         */
        class WebSession : public yancy::http::HttpSession
        {
        public:
            typedef std::shared_ptr<WebSession> ptr;
            
            WebSession(Socket::ptr sock, bool owner = true);

            yancy::http::HttpRequest::ptr handleShake();

            WebMessage::ptr recvMessage();
            int32_t sendMessage(WebMessage::ptr web_message,bool fin = true);
            int32_t sendMessage(const std::string& msg,int32_t frame_head = WSFrameHead::OPCODE::TEXT_FRAME,bool fin = true);
        
            int32_t ping();
            int32_t pong();

        private:
            bool handleServerShake();
            bool handleClientShake();
        };

        WebMessage::ptr WSRecvMessage(Stream* stream, bool client);
        int32_t WSSendMessage(Stream* stream, WebMessage::ptr msg, bool client, bool fin);
        int32_t WSPing(Stream* stream);
        int32_t WSPong(Stream* stream);

    }
}

#endif