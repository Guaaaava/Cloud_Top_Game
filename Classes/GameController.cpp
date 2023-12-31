#include "GameController.h"
#include "CTGScene.h"

GameController* GameController::_instance = nullptr;

GameController::GameController()
	: _shop(nullptr), _chessBoard(nullptr), enemyMoney(0), enemyExp(0), enemyLevel(0)
{
	_shop = Shop::create();
	_shop->retain();

	_chessBoard = ChessBoard::create();
	_chessBoard->retain();
}

GameController::~GameController()
{
	CC_SAFE_RELEASE_NULL(_shop);
	CC_SAFE_RELEASE_NULL(_chessBoard);
	GameController::destroyInstance();
}

GameController* GameController::getInstance()
{
	if (_instance == nullptr) {
		_instance = new GameController();
	}

	return _instance;
}

void GameController::destroyInstance()
{
	if (_instance != nullptr) {
		delete _instance;
		_instance = nullptr;
	}
}

bool GameController::isInMyBound(Command pos)
{
	return (pos._x >= 0 && pos._x < BDSZ_X / 2 && pos._y >= 0 && pos._y < BDSZ_Y / 2);
}

bool GameController::hasHero(Command pos)
{
	auto board = _chessBoard->getBoard();
	return (!isInMyBound(pos) || (*board)[pos._x][pos._y] != nullptr);
}

void GameController::placeHero(Hero* hero, Command pos)
{
	auto board = _chessBoard->getBoard();
	(*board)[pos._x][pos._y] = hero;
}

int GameController::IsEnd()
{
	bool myWin = true;
	bool enemyWin = true;

	if (myWin) {
		return M_WIN;
	}
	else if (enemyWin) {
		return E_WIN;
	}
	else {
		return DRAW;
	}
}

void GameController::createHeroInChessBoard(int idxOfHero)
{
	if (idxOfHero <= 0 || idxOfHero > NUM_CHESS)
	{
		CCLOG("idxOfHero:%d超过了最大编号%d，英雄创建失败！\n", idxOfHero, NUM_CHESS);
		return;
	}

	auto newHero = Samurai::create();
	newHero->setScale(0.2f);
	CTGScene::getLayer()->addChild(newHero, 3);
	newHero->setPosition(500, 600);

	_chessBoard->getMyHeroes()->push_back(newHero);
	_chessBoard->getMyHeroesIdxMap()->insert({ newHero, idxOfHero });
}

void GameController::sellHero(Hero* soldHero)
{
	auto myHeroes = _chessBoard->getMyHeroes();
	if (myHeroes == nullptr)
	{
		CCLOG("棋盘内无英雄，英雄出售失败！\n");
		return;
	}

	int idxOfHero = _chessBoard->findHero(soldHero);
	if (idxOfHero == -1)
	{
		CCLOG("不存在编号为%d的英雄，出售失败！\n", idxOfHero);
		return;
	}

	myHeroes->remove(soldHero);
	soldHero->removeFromParentAndCleanup(true);
	_shop->addMoney(_shop->getHeroPrice(idxOfHero));
	_shop->updateLevelLabel();
	_shop->updateMoneyLabel();
	_shop->updateButtonState();
}