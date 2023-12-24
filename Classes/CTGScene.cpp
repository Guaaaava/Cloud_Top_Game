#include "CTGScene.h"
#include "ConfigController.h"
#include "GameController.h"

/****************************************************
 * ���ܣ���ʼ������
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��7��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
LayerColor* CTGScene::layer = nullptr;			// Ϊ��̬��Ա����ռ䣨��Ҫ������
bool CTGScene::init()
{
	if (!Scene::init())
		return false;

	// ��ȡ��Ļ���ĵ�
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// ������
	layer = LayerColor::create(Color4B::WHITE);	// ��������ɫΪ��ɫ
	layer->setPosition(origin);
	layer->setContentSize(visibleSize);
	this->addChild(layer);

	// ��ս���������飩
	auto sceneChessBoard = Sprite::create("ChessBoardScene.png");
	sceneChessBoard->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	layer->addChild(sceneChessBoard, 1);			// ��ս���� z ֵΪ 1

	Shop* shop = GameController::getInstance()->getShop();

	return true;
}
