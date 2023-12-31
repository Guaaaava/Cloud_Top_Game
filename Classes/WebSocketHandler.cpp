// WebSocketHandler.cpp
/****************************************************
 * ���ܣ�ʹ��WebSocket������������Ϊ�ͻ���
 * ���ߣ�ĲӾ��
 * ʱ�䣺2023��12��21��
 * **************************************************
 * CopyRight 2023 by ĲӾ��
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

// Ӧ����void������֪����ô����������ʷ���bool��ͨ��������Ⱦ�ж�
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
    // �Ͽ�WebSocket����
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
#include "cocos2d.h" // ���������Ϊ��CCLOG����ɺ����ȥ��

WebSocketManager* WebSocketManager::getInstance() {
    static WebSocketManager instance;
    return &instance;
}

WebSocketManager::WebSocketManager() {
    client.init_asio();
    //���ֲ�ͬ��д��
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
        // �������Ӵ��¼�
        CCLOG("WebSocket connection opened");
        };

    // Define a connection initialization function (not needed for open_handler)
    auto init_func = [this, &ec](websocketpp::connection_hdl hdl) -> websocketpp::lib::error_code {
        client.send(hdl, "WebSocket handshake", websocketpp::frame::opcode::text, ec);
        if (ec) {
            // �������Ӵ���
            CCLOG("WebSocket initialization error: %s", ec.message().c_str());
            return ec;
        }

        return websocketpp::lib::error_code();
        };

    connectionHandle = client.get_connection(serverAddress, ec);
    if (ec) {
        // �������Ӵ���
        CCLOG("WebSocket connection error: %s", ec.message().c_str());
        return;
    }

    client.set_open_handler(open_func);  // �������Ӵ��¼��������
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
    // �������ӳɹ��¼�
    CCLOG("WebSocket onOpen");
}

void WebSocketManager::onClose(websocketpp::connection_hdl hdl) {
    // �������ӹر��¼�
    connectionHandle.reset();
    CCLOG("WebSocket onClose");
}

void WebSocketManager::onMessage(websocketpp::connection_hdl hdl, client_type::message_ptr msg) {
    // �����յ�����Ϣ
    CCLOG("WebSocket onMessage: %s", msg->get_payload().c_str());
}
*/