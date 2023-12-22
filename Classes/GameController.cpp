#include "GameController.h"

GameController* GameController::instance = nullptr;
GameController* GameController::getInstance()
{
    if (!instance)
    {
        instance = new GameController();
    }
    return instance;
}

void GameController::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

GameController::~GameController()
{
}
