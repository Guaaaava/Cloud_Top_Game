#pragma once

/****************************************************
 * 功能：使用WebSocketpp控制联机，作为客户端
 * 作者：牟泳祯
 * 时间：2023年12月23日
 * 说明：以下代码中的websocketpp相关头文件来自WebSocketpp开源库，链接https://github.com/zaphoyd/websocketpp
 *       实现框架参考websocketpp说明文档，链接https://docs.websocketpp.org/
 *       根据项目需要进行改动，并添加了自己的方法
 * **************************************************
 * CopyRight 2023 by 牟泳祯
 * **************************************************/

 // The ASIO_STANDALONE define is necessary to use the standalone version of Asio.
 // Remove if you are using Boost Asio.
 /*
   * Copyright (c) 2015, Peter Thorson. All rights reserved.
   *
   * Redistribution and use in source and binary forms, with or without
   * modification, are permitted provided that the following conditions are met:
   *     * Redistributions of source code must retain the above copyright
   *       notice, this list of conditions and the following disclaimer.
   *     * Redistributions in binary form must reproduce the above copyright
   *       notice, this list of conditions and the following disclaimer in the
   *       documentation and/or other materials provided with the distribution.
   *     * Neither the name of the WebSocket++ Project nor the
   *       names of its contributors may be used to endorse or promote products
   *       derived from this software without specific prior written permission.
   *
   * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
   * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
   * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
   */

   // **NOTE:** This file is a snapshot of the WebSocket++ utility server tutorial.
   // Additional related material can be found in the tutorials/utility_server
   // directory of the WebSocket++ repository.

   // The ASIO_STANDALONE define is necessary to use the standalone version of Asio.
   // Remove if you are using Boost Asio.

#define ASIO_STANDALONE

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <functional>

#include <unordered_set>


typedef websocketpp::server<websocketpp::config::asio> server;

struct ConnectionHash {
    std::size_t operator()(const websocketpp::connection_hdl& hdl) const {
        return std::hash<std::shared_ptr<void>>{}(hdl.lock());
    }
};

struct ConnectionEqual {
    bool operator()(const websocketpp::connection_hdl& lhs, const websocketpp::connection_hdl& rhs) const {
        // Compare the underlying shared pointers
        return lhs.lock() == rhs.lock();
    }
};

class utility_server {
public:
    utility_server() {
        // Set logging settings
        m_endpoint.set_error_channels(websocketpp::log::elevel::all);
        m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

        // Initialize Asio
        m_endpoint.init_asio();

        // Set the default message handler to the echo handler
        m_endpoint.set_message_handler(std::bind(
            &utility_server::echo_handler, this,
            std::placeholders::_1, std::placeholders::_2
        ));

        // 以下为自定义
        m_endpoint.set_open_handler(std::bind(
            &utility_server::on_open, this, std::placeholders::_1
        ));

        m_endpoint.set_close_handler(std::bind(
            &utility_server::on_close, this, std::placeholders::_1
        ));
    }

    void echo_handler(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        // write a new message
        int id_num = 0;
        for (auto it : m_connections) {
            id_num++;
            if (it.lock().get() != hdl.lock().get()) { // Skip the sender
                m_endpoint.send(it, msg->get_payload(), msg->get_opcode());
            }
        }
        /* 这是直接向来信方发送消息的方法
        void echo_handler(websocketpp::connection_hdl hdl, server::message_ptr msg) {
         // write a new message
         m_endpoint.send(hdl, msg->get_payload(), msg->get_opcode());
     }
        */
    }

    void on_open(websocketpp::connection_hdl hdl) {
        // Add the new connection to the set of connections
        m_connections.insert(hdl);
    }

    void on_close(websocketpp::connection_hdl hdl) {
        // Remove the closed connection from the set of connections
        m_connections.erase(hdl);
    }
    void run() {
        // Listen on port 9002
        m_endpoint.listen(9002);

        // Queues a connection accept operation
        m_endpoint.start_accept();

        // Start the Asio io_service run loop
        m_endpoint.run();
    }
private:
    server m_endpoint;
    std::unordered_set<websocketpp::connection_hdl, ConnectionHash, ConnectionEqual> m_connections;
};

int main() {
    utility_server s;
    s.run();
    return 0;
}