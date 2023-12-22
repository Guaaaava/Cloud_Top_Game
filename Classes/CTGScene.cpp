#include "CTGScene.h"
#include "ConfigController.h"

/****************************************************
 * ���ܣ���ʼ������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��7��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
bool CTGScene::init()
{
	if (!Scene::init())
		return false;

	// ���������¼�������
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);		// �����¼���û
	listener->onTouchBegan = CC_CALLBACK_2(CTGScene::onTouchBegan, this);		// ���ð��°�ť�Ļص�
	listener->onTouchEnded = CC_CALLBACK_2(CTGScene::onTouchEnded, this);		// �����ͷŰ�ť�Ļص�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// ��ȡ��Ļ���ĵ�
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ���ñ�����ɫ����ǰΪ��ɫ��
	auto layer = LayerColor::create(Color4B::WHITE);
	layer->setPosition(origin);
	layer->setContentSize(visibleSize);
	this->addChild(layer);

	// ��ս���������飩
	auto boardNode = Sprite::create("BoardScene.png");
	boardNode->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer->addChild(boardNode, 1);			// ��ս���� z ֵΪ 1
	prt_backGround = boardNode;

	// ����������ģ��Ҳ�����
	Vec2 leftOrigin = origin + Vec2(visibleSize.width * 0.05f, visibleSize.height / 2);
	Vec2 rightOrigin = origin + Vec2(visibleSize.width * 0.95f, visibleSize.height / 2);

	// ������ť

	// ��ʼ��Ϸ��ť
	std::string words = ConfigController::getInstance()->getCNByID(WORDS_START);
	auto startItem = CTGScene::createGameButton(words, CC_CALLBACK_1(CTGScene::menuStartCallback, this));
	float x = leftOrigin.x;
	float y = leftOrigin.y + visibleSize.height * 0.4f;
	startItem->setPosition(Vec2(x, y));			// �ڽ������Ͻ�

	// ���̵갴ť
	words = ConfigController::getInstance()->getCNByID(WORDS_SHOP);
	auto openShopItem = CTGScene::createGameButton(words, CC_CALLBACK_1(CTGScene::menuOpenShopCallback, this));
	x = rightOrigin.x;
	y = rightOrigin.y - visibleSize.height * 0.4f;
	openShopItem->setPosition(Vec2(x, y));		// �ڽ������½�

	// �˳���Ϸ��ť
	words = ConfigController::getInstance()->getCNByID(WORDS_EXIT);
	auto exitGameItem = CTGScene::createGameButton(words, CC_CALLBACK_1(CTGScene::menuExitGameCallback, this));
	x = leftOrigin.x + exitGameItem->getContentSize().width * 1.5f;
	y = leftOrigin.y + visibleSize.height * 0.4f;
	exitGameItem->setPosition(Vec2(x, y));		// �ڽ������Ͻǡ���ʼ����ť�ұ�

	// ��������˵������飩
	auto menu = Menu::create(startItem, openShopItem, exitGameItem, nullptr);
	menu->setPosition(origin);
	layer->addChild(menu, 3);			// ����˵� z ֵΪ 3

	// �̵갴ť��С
	float padding = 100;				// ��ťͼƬ��100���أ���100����
	Size shopButtonSize = Size(padding, padding);
	Vec2 _origin = Vec2(rightOrigin.x, rightOrigin.y - visibleSize.height * 0.4f);
	prt_shopButtonSize = Rect(_origin, shopButtonSize);

	return true;
}

/****************************************************
 * ���ܣ�����ͨ�ð�ť
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��11��
 * ������nameΪ��ť��ǩ��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
MenuItemImage* CTGScene::createGameButton(std::string name, const ccMenuCallback& callback)
{
	std::string picPath = "BottonScene_100x100.png";
	// ����һ��ͼƬ�˵���
	auto item = MenuItemImage::create(picPath, picPath, callback);

	// ��ť���ֱ�ǩ
	auto label = Label::createWithTTF(name, "fonts/simkai.ttf", 36);	// ���ñ�ǩ������ֺţ���ǰΪ�п���
	label->setPosition(item->getContentSize() / 2);	// ���ñ�ǩ����
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);		// ���ñ�ǩê�㣨��ǰΪ���ģ�
	label->setColor(Color3B::BLACK);				// ���ñ�ǩ��ɫ����ǰΪ��ɫ��
	item->addChild(label);

	return item;
}

/****************************************************
 * ���ܣ�ʵ����Ϸ��ʼ��ť�ĵ���¼�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��11��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void CTGScene::menuStartCallback(Ref* sender)
{
	// ���ý���
}

/****************************************************
 * ���ܣ�ʵ�ִ��̵갴ť�ĵ���¼�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��11��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void CTGScene::menuOpenShopCallback(Ref* sender)
{
	// ��ʱ������qwq
}

/****************************************************
 * ���ܣ�ʵ���˳���Ϸ��ť�ĵ���¼�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��11��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void CTGScene::menuExitGameCallback(Ref* sender)
{
	// ��ʱ������qwq
}

/****************************************************
 * ���ܣ�ʵ�ְ��°�ť�Ļص�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��12��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
bool CTGScene::onTouchBegan(Touch* touch, Event* event)
{
	// Ĭ�ϴ���
	return true;
}

/****************************************************
 * ���ܣ�ʵ���ͷŰ�ť�Ļص������̵꣩
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��12��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void CTGScene::onTouchEnded(Touch* touch, Event* event)
{
	// ��ǰ�����������
	Vec2 position = touch->getLocation();

	// �ж�������ڲ����̵갴ť��
	if (prt_shopButtonSize.containsPoint(position))
	{
		// ��ʾһ���̵꾫��
		// createShopNode();
	}
}

void CTGScene::createShopNode()
{
	Sprite* shopNode = Sprite::create("ShopScene_1000x400.png");
	// shopNode->setPosition()
	prt_backGround->addChild(shopNode, 4);	// �̵� z ֵΪ 4
}
