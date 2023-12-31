#include "ChessBoard.h"
#include "cocos2d.h"
/****************************************************
 * ���ܣ���ʼ�����̣���ʼ���ɹ�����true����֮����false
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
bool ChessBoard::init()
{
	// ��ʼ����Ա
	_BOARD.resize(BDSZ_Y);
	for (int i = 0; i < BDSZ_Y; i++) {
		_BOARD[i].resize(BDSZ_X);
	}

	return true;
}

/****************************************************
 * ���ܣ���ѯ�ҷ������Ƿ����ָ��Ӣ�ۣ��������򷵻ر�ţ����򷵻�-1
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
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
//����
void F()
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    const int numRows1 = 3;  // ��һ�����������
    const int numCols1 = 10;  // ��һ�����������
    const int totalBlocks1 = numRows1 * numCols1;  // ��һ�����������

    // �����һ������ÿ������Ŀ�Ⱥ͸߶�
    float blockWidth1 = visibleSize.width * 0.64f / numCols1;
    float blockHeight1 = visibleSize.height * 0.12f / numRows1;

    // ������ά�������洢��һ�������������Ϣ
    std::vector<std::vector<Rect>> blocks1(numRows1, std::vector<Rect>(numCols1));

    // ��ʼ����һ������ÿ�������λ�úʹ�С
    for (int row = 0; row < numRows1; row++) {
        for (int col = 0; col < numCols1; col++) {
            float x = origin.x + visibleSize.width * 0.18f + blockWidth1 * col + blockWidth1 / 2;
            float y = origin.y + visibleSize.height * 0.57f + blockHeight1 * row + blockHeight1 / 2;
            blocks1[row][col] = Rect(x - blockWidth1 / 2, y - blockHeight1 / 2, blockWidth1, blockHeight1);
        }
    }

    const int numRows2 = 1;  // �ڶ������������
    const int numCols2 = 9;  // �ڶ������������
    const int totalBlocks2 = numRows2 * numCols2;  // �ڶ������������

    // ����ڶ�������ÿ������Ŀ�Ⱥ͸߶�
    float blockWidth2 = visibleSize.width * 0.62f / numCols2;
    float blockHeight2 = visibleSize.height * 0.06f / numRows2;

    // ������ά�������洢�ڶ��������������Ϣ
    std::vector<std::vector<Rect>> blocks2(numRows2, std::vector<Rect>(numCols2));

    // ��ʼ���ڶ�������ÿ�������λ�úʹ�С
    for (int row = 0; row < numRows2; row++) {
        for (int col = 0; col < numCols2; col++) {
            float x = origin.x + visibleSize.width * 0.18f + blockWidth2 * col + blockWidth2 / 2;
            float y = origin.y + visibleSize.height * 0.31f + blockHeight2 * row + blockHeight2 / 2;
            blocks2[row][col] = Rect(x - blockWidth2 / 2, y - blockHeight2 / 2, blockWidth2, blockHeight2);
        }
    }

    // ������������¼�����������Ϣ
    std::vector<Rect> allBlocks;

    // ����һ�������������Ϣ��������
    for (int row = 0; row < numRows1; row++) {
        for (int col = 0; col < numCols1; col++) {
            allBlocks.push_back(blocks1[row][col]);
        }
    }

    // ���ڶ��������������Ϣ��������
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

    //// ��갴���¼�
    //auto listener = EventListenerMouse::create();
    //listener->onMouseDown = [&](EventMouse* event) {
    //    if (mySprite->getBoundingBox().containsPoint(event->getLocation())) {
    //        isDragging = true;
    //    }
    //};

    //// ����ƶ��¼�
    //listener->onMouseMove = [&](EventMouse* event) {
    //    if (isDragging) {
    //        mySprite->setPosition(event->getLocation());
    //    }
    //};

    //// ����ͷ��¼�
    //listener->onMouseUp = [&](EventMouse* event) {
    //    if (isDragging) {
    //        isDragging = false;
    //    }
    //};
    //Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, mySprite);









}