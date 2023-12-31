#pragma once

/****************************************************
 * 功能：游戏逻辑控制器
 * 作者：黄辰宇
 * 时间：2023年12月14日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
class GameController
{
public:
	static GameController* getInstance();
	static void destroyInstance();
	~GameController();

	// 对战过程


	// 胜负判定
	

private:
	static GameController* instance;
};