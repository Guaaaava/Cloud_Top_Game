#pragma once
/****************************************************
 * 功能：使用WebSocket控制联机，作为服务器端，现只有头文件
 * 作者：牟泳祯
 * 时间：2023年12月21日
 * **************************************************
 * CopyRight 2023 by 牟泳祯
 * **************************************************/
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <unordered_set>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// WebSocket服务器类
class WebSocketServer {
public:
    WebSocketServer() {
        server.init_asio();
        server.set_message_handler(bind(&WebSocketServer::onMessage, this, _1, _2));
        server.set_open_handler(bind(&WebSocketServer::onOpen, this, _1));
        server.set_close_handler(bind(&WebSocketServer::onClose, this, _1));
    }

    void start(int port) {
        server.listen(port);
        server.start_accept();
        server.run();
    }

private:
    typedef websocketpp::server<websocketpp::config::asio> server_type;
    server_type server;
    std::unordered_set<websocketpp::connection_hdl, std::hash<websocketpp::connection_hdl>> connections;
    
    void onOpen(websocketpp::connection_hdl hdl) {
        // 添加新连接到集合中
        connections.insert(hdl);
    }

    void onClose(websocketpp::connection_hdl hdl) {
        // 连接关闭时从集合中移除
        connections.erase(hdl);
    }

    void onMessage(websocketpp::connection_hdl hdl, server_type::message_ptr msg) {
        // 处理收到的消息
        std::string message = msg->get_payload();
        // 在这里可以处理游戏逻辑，并向其他连接的客户端广播消息
        broadcastMessage(message);
    }

    void broadcastMessage(const std::string& message) {
        for (auto it : connections) {
            server.send(it, message, websocketpp::frame::opcode::text);
        }
    }
};

int main() {
    WebSocketServer server;
    server.start(9002);  // WebSocket服务器监听的端口
    return 0;
}





/*
#include <cocos/network/http_listener.h>
#include <cocos/network/websocket.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;
using namespace web::websockets::experimental::listener;

class WebSocketServer {
public:
    WebSocketServer(const utility::string_t& url) : listener_(url) {
        listener_.support(web::http::methods::GET, [this](web::http::http_request request) {
            handle_get(request);
            });
    }

    void run() {
        listener_.open().wait();
        listener_.close().wait();
    }

private:
    void handle_get(web::http::http_request request) {
        if (websocket::is_request_valid(request)) {
            websocket::http_websocket_context context = websocket::handle_request(request);

            context.websocket().set_message_handler([this](websocket::message_ptr msg) {
                handle_message(msg);
                });

            context.websocket().set_close_handler([this](websocket::close_status status, utility::string_t reason, const std::error_code& error) {
                handle_close(status, reason, error);
                });

            // Accept the WebSocket handshake
            request.reply(web::http::status_codes::SwitchingProtocols, U("Switching Protocols"), web::http::headers::Upgrade(U("websocket")));
        }
        else {
            // Handle non-WebSocket requests here
            request.reply(web::http::status_codes::OK);
        }
    }

    void handle_message(websocket::message_ptr msg) {
        // Handle WebSocket messages
        auto utf8_message = msg->extract_utf8string().get();
        // Process the received message...
    }

    void handle_close(websocket::close_status status, const utility::string_t& reason, const std::error_code& error) {
        // Handle WebSocket close event
    }

    http_listener listener_;
};

int main() {
    utility::string_t url = U("http://localhost:9002");
    WebSocketServer server(url);
    server.run();

    return 0;
}
*/