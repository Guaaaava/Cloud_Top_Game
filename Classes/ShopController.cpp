#include "CTGScene.h"
#include "ShopController.h"
#include "ConfigController.h"

/****************************************************
 * 功能：商店控制器默认函数
 * 作者：黄辰宇
 * 时间：2023年12月22日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
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
 * 功能：创建弈子通用按钮
 * 参数：未被选中时的图片路径，被选中时的图片路径，
 *      向量position不包含origin
 *      （静态成员，可以直接调用）
 * 作者：黄辰宇
 * 时间：2023年12月22日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
Button* ShopController::createChessButton(const std::string normalPicPath, const std::string selectedPicPath, const Vec2 position)
{
    const auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto buttonChess = Button::create(normalPicPath, selectedPicPath);  // 创建按钮

    // 获取中文
    // 设置按钮文字
    // 设置字体
    // 设置字号
    // 设置文字颜色

    buttonChess->setPosition(position);	// 设置位置

    return buttonChess;
}

/****************************************************
 * 功能：获取从左到右五张卡牌中心位置
 * 参数：从左到右第几张卡牌
 *      （静态成员，可以直接调用）
 * 作者：黄辰宇
 * 时间：2023年12月22日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
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
