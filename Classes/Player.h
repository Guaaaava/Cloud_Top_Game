#pragma once
/****************************************************
 * ���ܣ��洢�����Ϣ
 * ���ߣ�ĲӾ��
 * ʱ�䣺2023��12��22��
 * ���⣺����Ϸ�����У���Ҫ�����������µĴ���洢�����Ϣ
 * Player currentPlayer("Player1", "your-server-address", 9002);
 * auto wsManager = WebSocketManager::getInstance();
 * wsManager->connect("ws://" + currentPlayer.getServerAddress() + ":" + std::to_string(currentPlayer.getServerPort()));
 * ���Ƿ������Ҫ�ٿ���
 * **************************************************
 * CopyRight 2023 by ĲӾ��
 * **************************************************/
#include <string>

class Player {
public:
    Player(const std::string& playerName, const std::string& serverAddress, int serverPort);

    const std::string& getPlayerName() const;
    const std::string& getServerAddress() const;
    int getServerPort() const;

private:
    std::string playerName;
    std::string serverAddress;
    int serverPort;
};