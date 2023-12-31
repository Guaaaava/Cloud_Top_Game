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
#include "Player.h"

Player::Player(const std::string& playerName, const std::string& serverAddress, int serverPort)
    : playerName(playerName), serverAddress(serverAddress), serverPort(serverPort) {}

const std::string& Player::getPlayerName() const {
    return playerName;
}

const std::string& Player::getServerAddress() const {
    return serverAddress;
}

int Player::getServerPort() const {
    return serverPort;
}