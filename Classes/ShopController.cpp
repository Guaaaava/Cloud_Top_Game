#include "CTGScene.h"
#include "ShopController.h"
#include "ConfigController.h"

/****************************************************
 * ���ܣ��̵������Ĭ�Ϻ���
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��22��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
ShopController* ShopController::instance = nullptr;
ShopController* ShopController::getInstance()
{
    if (!instance)
    {
        instance = new ShopController();
    }
    return instance;
}
void ShopController::destroyInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}
ShopController::~ShopController()
{
}

/****************************************************
 * ���ܣ���������ͨ�ð�ť
 * ������δ��ѡ��ʱ��ͼƬ·������ѡ��ʱ��ͼƬ·����
 *      ����position������origin
 *      ����̬��Ա������ֱ�ӵ��ã�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��22��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
Button* ShopController::createChessButton(const std::string normalPicPath, const std::string selectedPicPath, const Vec2 position)
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto buttonChess = Button::create(normalPicPath, selectedPicPath);  // ������ť

    // ��ȡ����
    // ���ð�ť����
    // ��������
    // �����ֺ�
    // ����������ɫ

    buttonChess->setPosition(position);	// ����λ��

    return buttonChess;
}

/****************************************************
 * ���ܣ���ȡ���������ſ�������λ��
 * �����������ҵڼ��ſ���
 *      ����̬��Ա������ֱ�ӵ��ã�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��22��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
Vec2 ShopController::getChessPosition(const int numofChess)
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 position = origin;

    const float chessMiddle_x = getInstance()->shopStart_x + (numofChess - 1) * getInstance()->chessWidth + getInstance()->chessWidth / 2.0f;
    position = origin + Vec2(chessMiddle_x, SHOP_HEIGHT / 2.0f);

    return position;
}
