/****************************************************
 * 功能：存储玩家信息
 * 作者：牟泳祯
 * 时间：2023年12月22日
 * 问题：在游戏场景中，需要有类似于以下的代码存储玩家信息
 * Player currentPlayer("Player1", "your-server-address", 9002);
 * auto wsManager = WebSocketManager::getInstance();
 * wsManager->connect("ws://" + currentPlayer.getServerAddress() + ":" + std::to_string(currentPlayer.getServerPort()));
 * 这是否合理需要再考虑
 * **************************************************
 * CopyRight 2023 by 牟泳祯
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