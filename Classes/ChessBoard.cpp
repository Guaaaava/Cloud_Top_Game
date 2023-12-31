#include "ChessBoard.h"
#include "cocos2d.h"
/****************************************************
 * 功能：初始化棋盘，初始化成功返回true，反之返回false
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
bool ChessBoard::init()
{
	// 初始化成员
	_BOARD.resize(BDSZ_Y);
	for (int i = 0; i < BDSZ_Y; i++) {
		_BOARD[i].resize(BDSZ_X);
	}

	return true;
}

/****************************************************
 * 功能：查询我方场上是否存在指定英雄，若存在则返回编号，否则返回-1
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
int ChessBoard::findHero(Hero* hero)
{
	std::list<Hero*>::iterator it;
	for (it = _myHeroes.begin(); it != _myHeroes.end(); it++)
	{
		if ((*it) == hero)
		{
			return _myHeroesIdx[hero];
		}
	}

	return -1;
}
//回显
void F()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    const int numRows1 = 3;  // 第一块区域的行数
    const int numCols1 = 10;  // 第一块区域的列数
    const int totalBlocks1 = numRows1 * numCols1;  // 第一块区域的总数

    // 计算第一块区域每个区域的宽度和高度
    float blockWidth1 = visibleSize.width * 0.64f / numCols1;
    float blockHeight1 = visibleSize.height * 0.12f / numRows1;

    // 创建二维数组来存储第一块区域的区域信息
    std::vector<std::vector<Rect>> blocks1(numRows1, std::vector<Rect>(numCols1));

    // 初始化第一块区域每个区域的位置和大小
    for (int row = 0; row < numRows1; row++) {
        for (int col = 0; col < numCols1; col++) {
            float x = origin.x + visibleSize.width * 0.18f + blockWidth1 * col + blockWidth1 / 2;
            float y = origin.y + visibleSize.height * 0.57f + blockHeight1 * row + blockHeight1 / 2;
            blocks1[row][col] = Rect(x - blockWidth1 / 2, y - blockHeight1 / 2, blockWidth1, blockHeight1);
        }
    }

    const int numRows2 = 1;  // 第二块区域的行数
    const int numCols2 = 9;  // 第二块区域的列数
    const int totalBlocks2 = numRows2 * numCols2;  // 第二块区域的总数

    // 计算第二块区域每个区域的宽度和高度
    float blockWidth2 = visibleSize.width * 0.62f / numCols2;
    float blockHeight2 = visibleSize.height * 0.06f / numRows2;

    // 创建二维数组来存储第二块区域的区域信息
    std::vector<std::vector<Rect>> blocks2(numRows2, std::vector<Rect>(numCols2));

    // 初始化第二块区域每个区域的位置和大小
    for (int row = 0; row < numRows2; row++) {
        for (int col = 0; col < numCols2; col++) {
            float x = origin.x + visibleSize.width * 0.18f + blockWidth2 * col + blockWidth2 / 2;
            float y = origin.y + visibleSize.height * 0.31f + blockHeight2 * row + blockHeight2 / 2;
            blocks2[row][col] = Rect(x - blockWidth2 / 2, y - blockHeight2 / 2, blockWidth2, blockHeight2);
        }
    }

    // 创建容器来记录所有区域的信息
    std::vector<Rect> allBlocks;

    // 将第一块区域的区域信息加入容器
    for (int row = 0; row < numRows1; row++) {
        for (int col = 0; col < numCols1; col++) {
            allBlocks.push_back(blocks1[row][col]);
        }
    }

    // 将第二块区域的区域信息加入容器
    for (int row = 0; row < numRows2; row++) {
        for (int col = 0; col < numCols2; col++) {
            allBlocks.push_back(blocks2[row][col]);
        }
    }
    

    auto mySprite = Sprite::create("test.png");
    mySprite->setScale(0.5);
    //CTGScene::getLayer()->addChild(mySprite, 10);
    mySprite->setPosition(origin + visibleSize / 2);

    bool isDragging = false;
    Vec2 offset = Vec2::ZERO;

    auto listener = EventListenerMouse::create();
    listener->onMouseDown = [&](EventMouse* event)
    {
        if (mySprite->getBoundingBox().containsPoint(event->getLocationInView()))
        {
            isDragging = true;
            offset = mySprite->getPosition() - event->getLocationInView();
        }
    };

    listener->onMouseMove = [&](EventMouse* event)
    {
        if (isDragging)
        {
            mySprite->setPosition(event->getLocationInView() + offset);
        }
    };

    listener->onMouseUp = [&](EventMouse* event)
    {
        if (isDragging)
        {
            isDragging = false;
            mySprite->setPosition(event->getLocationInView());
        }
    };

    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, mySprite);
    //const auto visibleSize = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto mySprite = Sprite::create("test.png");

    //mySprite->setScale(0.5);


    //mySprite->setPosition(origin + visibleSize / 2);

    //bool isDragging = false;

    //// 鼠标按下事件
    //auto listener = EventListenerMouse::create();
    //listener->onMouseDown = [&](EventMouse* event) {
    //    if (mySprite->getBoundingBox().containsPoint(event->getLocation())) {
    //        isDragging = true;
    //    }
    //};

    //// 鼠标移动事件
    //listener->onMouseMove = [&](EventMouse* event) {
    //    if (isDragging) {
    //        mySprite->setPosition(event->getLocation());
    //    }
    //};

    //// 鼠标释放事件
    //listener->onMouseUp = [&](EventMouse* event) {
    //    if (isDragging) {
    //        isDragging = false;
    //    }
    //};
    //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, mySprite);









}