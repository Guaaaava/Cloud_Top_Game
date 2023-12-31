// WebSocketHandler.cpp
/****************************************************
 * 功能：使用WebSocket控制联机，作为客户端
 * 作者：牟泳祯
 * 时间：2023年12月21日
 * **************************************************
 * CopyRight 2023 by 牟泳祯
 * **************************************************/
/*
#include "WebSocketHandler.h"
#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::network;

WebSocketHandler* WebSocketHandler::getInstance()
{
    static WebSocketHandler instance;
    return &instance;
}

WebSocketHandler::WebSocketHandler() : webSocket(nullptr)
{
    init();
}

WebSocketHandler::~WebSocketHandler()
{
    if (webSocket)
    {
        webSocket->close();
        CC_SAFE_DELETE(webSocket);
    }
}

bool WebSocketHandler::init()
{
    return true;
}

// 应该是void，但不知道怎么检验输出，故返回bool，通过场景渲染判断
bool WebSocketHandler::connectToServer(const std::string& serverAddress)
{
    webSocket = new WebSocket();
    if (webSocket->init(*this, serverAddress))
    {
        CCLOG("WebSocket connected to %s", serverAddress.c_str());
        //std::cout << "success" << std::endl;
        return true;
    }
    else {
        CCLOG("WebSocket Fail to connect to %s", serverAddress.c_str());
        //std::cout << "error" << std::endl;
        return false;
    }
}

void WebSocketHandler::send(const std::string& message)
{
    while (webSocket->getReadyState() != WebSocket::State::OPEN)
        ;
    if (webSocket && webSocket->getReadyState() == WebSocket::State::OPEN)
    {
        webSocket->send(message);
        CCLOG("the message %s Success to send", message);
    }
    else {
        auto x = webSocket->getReadyState();
        CCLOG("%d", x);
        CCLOG("the message %s Fail to send", message);
    }
}

void WebSocketHandler::disconnect()
{
    if (webSocket)
    {
        webSocket->close();
        CC_SAFE_DELETE(webSocket);
        CCLOG("WebSocket connection disconnected");
    }
}

void WebSocketHandler::setMessageCallback(const MessageCallback& callback)
{
    messageCallback = callback;
}

void WebSocketHandler::onOpen(WebSocket* ws)
{
    CCLOG("WebSocket connection opened");
}

void WebSocketHandler::onMessage(WebSocket* ws, const WebSocket::Data& data)
{
    std::string message(data.bytes);
    CCLOG("WebSocket received message: %s", message.c_str());
    if (messageCallback)
    {
        messageCallback(message);
    }
}

void WebSocketHandler::onClose(WebSocket* ws)
{
    CCLOG("WebSocket connection closed");
    // 断开WebSocket连接
    if (getInstance()->webSocket)
    {
        getInstance()->webSocket->close();
        CC_SAFE_DELETE(getInstance()->webSocket);
    }
}

void WebSocketHandler::onError(WebSocket* ws, const WebSocket::ErrorCode& error)
{
    CCLOG("WebSocket error with code: %d", static_cast<int>(error));
}
*/
/*
#include "WebSocketHandler.h"
#include "cocos2d.h" // 引用这个是为了CCLOG，完成后可以去掉

WebSocketManager* WebSocketManager::getInstance() {
    static WebSocketManager instance;
    return &instance;
}

WebSocketManager::WebSocketManager() {
    client.init_asio();
    //两种不同的写法
    //client.set_open_handler(std::bind(&WebSocketManager::onOpen, this, std::placeholders::_1));
    //client.set_close_handler(std::bind(&WebSocketManager::onClose, this, std::placeholders::_1));
    //client.set_message_handler(std::bind(&WebSocketManager::onMessage, this, std::placeholders::_1, std::placeholders::_2));
    
    client.set_open_handler([this](websocketpp::connection_hdl hdl) {
        onOpen(hdl);
        });
    client.set_close_handler([this](websocketpp::connection_hdl hdl) {
        onClose(hdl);
        });
    client.set_message_handler([this](websocketpp::connection_hdl hdl, client_type::message_ptr msg) {
        onMessage(hdl, msg);
        });
    // Initialize connectionHandle to avoid potential issues
    connectionHandle = nullptr;
}

WebSocketManager::~WebSocketManager() {
    // Ensure proper cleanup
    disconnect();
}

void WebSocketManager::connect(const std::string& serverAddress) {
    websocketpp::lib::error_code ec;

    // Define an open handler function
    auto open_func = [this](websocketpp::connection_hdl hdl) {
        // 处理连接打开事件
        CCLOG("WebSocket connection opened");
        };

    // Define a connection initialization function (not needed for open_handler)
    auto init_func = [this, &ec](websocketpp::connection_hdl hdl) -> websocketpp::lib::error_code {
        client.send(hdl, "WebSocket handshake", websocketpp::frame::opcode::text, ec);
        if (ec) {
            // 处理连接错误
            CCLOG("WebSocket initialization error: %s", ec.message().c_str());
            return ec;
        }

        return websocketpp::lib::error_code();
        };

    connectionHandle = client.get_connection(serverAddress, ec);
    if (ec) {
        // 处理连接错误
        CCLOG("WebSocket connection error: %s", ec.message().c_str());
        return;
    }

    client.set_open_handler(open_func);  // 设置连接打开事件处理程序
    client.connect(connectionHandle);
}


void WebSocketManager::disconnect() {
    if (connectionHandle) {
        CCLOG("WebSocket disconnecting...");
        client.close(connectionHandle, websocketpp::close::status::going_away, "Game disconnected");
        connectionHandle.reset();
        CCLOG("WebSocket disconnected");
    }
}

void WebSocketManager::sendMessage(const std::string& message) {
    if (connectionHandle) {
        CCLOG("WebSocket sending message: %s", message.c_str());
        client.send(connectionHandle, message, websocketpp::frame::opcode::text);
    }
}

void WebSocketManager::onOpen(websocketpp::connection_hdl hdl) {
    connectionHandle = client.get_con_from_hdl(hdl);
    // 处理连接成功事件
    CCLOG("WebSocket onOpen");
}

void WebSocketManager::onClose(websocketpp::connection_hdl hdl) {
    // 处理连接关闭事件
    connectionHandle.reset();
    CCLOG("WebSocket onClose");
}

void WebSocketManager::onMessage(websocketpp::connection_hdl hdl, client_type::message_ptr msg) {
    // 处理收到的消息
    CCLOG("WebSocket onMessage: %s", msg->get_payload().c_str());
}
*/