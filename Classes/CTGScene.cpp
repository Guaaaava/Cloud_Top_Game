#include "CTGScene.h"
<<<<<<< Updated upstream
=======
#include "ConfigController.h"
#include "ShopController.h"
>>>>>>> Stashed changes

bool CTGScene::init()
{
	if (!Scene::init())
		return false;

<<<<<<< Updated upstream
	// �����֮ս���Ʊ�ǩ
=======
	// ��ȡ��Ļ���ĵ�
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ����������
	layer = LayerColor::create(Color4B::WHITE);	// ��������ɫΪ��ɫ
	layer->setPosition(origin);
	layer->setContentSize(visibleSize);
	this->addChild(layer);

	// ��ս���������飩
	auto sceneChessBoard = Sprite::create("ChessBoardScene.png");
	sceneChessBoard->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer->addChild(sceneChessBoard, 1);			// ��ս���� z ֵΪ 1

	// ���������¼����������ѽ��ã�
/*
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);		// �����¼���û
	listener->onTouchBegan = CC_CALLBACK_2(CTGScene::onTouchBegan, this);		// ���ð��°�ť�Ļص�
	listener->onTouchEnded = CC_CALLBACK_2(CTGScene::onTouchEnded, this);		// �����ͷŰ�ť�Ļص�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
*/
>>>>>>> Stashed changes

	// ������ť
	std::string normalPicPath = "NormalLevelUpBotton.png";		// δ��ѡ��ʱ��ť��ʽ
	std::string selectedPicPath = "SelectedLevelUpBotton.png";	// ��ѡ��ʱ��ť��ʽ
	auto buttonLevelUp = Button::create(normalPicPath, selectedPicPath);// ������ť
	std::string words = ConfigController::getInstance()->getCNByID(WORDS_LEVELUP);	// ��ȡ���ġ�������
	buttonLevelUp->setTitleText(words);						// ���ð�ť����
	buttonLevelUp->setTitleFontName("fonts/simkai.ttf");	// ��������
	buttonLevelUp->setTitleFontSize(24.0f);					// �����ֺ�
	buttonLevelUp->setTitleColor(Color3B::BLACK);			// ������ɫ
	buttonLevelUp->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.75f));	// ����λ��
	layer->addChild(buttonLevelUp, 2);						// ��ť z ֵΪ 2

<<<<<<< Updated upstream
	// ��ս���������飩

	// ��ʼ��Ϸ��ť

	// ���̵갴ť

	// �˳���Ϸ��ť

	// �����֮սLOGO

=======
	// ����ֵ��ǩ

	// ˢ���̵갴ť
	normalPicPath = "NormalRefreshShopBotton.png";		// δ��ѡ��ʱ��ť��ʽ
	selectedPicPath = "SelectedRefreshShopBotton.png";	// ��ѡ��ʱ��ť��ʽ
	auto buttonRefreshShop = Button::create(normalPicPath, selectedPicPath);
	words = ConfigController::getInstance()->getCNByID(WORDS_REFRESH);	// ��ȡ���ġ�ˢ�¡�
	buttonRefreshShop->setTitleText(words);						// ���ð�ť����
	buttonRefreshShop->setTitleFontName("fonts/simkai.ttf");	// ��������
	buttonRefreshShop->setTitleFontSize(24.0f);					// �����ֺ�
	buttonRefreshShop->setTitleColor(Color3B::BLACK);			// ������ɫ
	buttonRefreshShop->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.25f));	// ����λ��
	layer->addChild(buttonRefreshShop, 2);						// ��ť z ֵΪ 2
	
	// ʣ���ұ�ǩ

	// �����̵꣨�����������ɣ�
	normalPicPath = static_cast<std::string>("chessButton/0.png");		// δ��ѡ��ʱ��ť��ʽ
	selectedPicPath = static_cast<std::string>("chessButton/0.png");	// ��ѡ��ʱ��ť��ʽ
	for (int num = 1; num <= 5; num++)
	{
		const int normalPathLength = normalPicPath.size();
		const int selectedPathLength = selectedPicPath.size();
		normalPicPath[12]++;
		selectedPicPath[12]++;

		auto chessPosition = ShopController::getChessPosition(num);
		auto buttonChess = ShopController::createChessButton(normalPicPath, selectedPicPath, chessPosition);
		layer->addChild(buttonChess, 2);	// ��ť z ֵΪ 2
	}
	
	
>>>>>>> Stashed changes

	return true;
}
