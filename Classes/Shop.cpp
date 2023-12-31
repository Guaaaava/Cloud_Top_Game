#include "CTGScene.h"
#include "Shop.h"
#include "GameController.h"

class Shop {
public:
    static constexpr int NUM_CHESS_SHOP = 10;
    static constexpr int NUM_CHESS = 10;
    static constexpr int MONEY_ADD_EXP = 10;
    static constexpr int EXP_ADD_ONCE = 10;

    bool init() {
        money = 20;
        expr = 0;
        level = 0;

        memset(chessButton, 0, sizeof(chessButton));

        createLevelUpAndRefreshButtons();
        createLabelsAndSprites();
        initAllChessPrice();
        createInitialChessButtons();
        getChessPrice();
        updateButtonState();

        return true;
    }

private:
    int money;
    int expr;
    int level;
    Button* chessButton[NUM_CHESS_SHOP];
    int allChessPrice[NUM_CHESS];
    int chessPrice[NUM_CHESS_SHOP];
    Button* buttonLevelUp;

    void createLevelUpAndRefreshButtons() {
        createLevelUpButton();
        createRefreshShopButton();
    }

    void createLevelUpButton() {
        std::string normalPicPath = "NormalLevelUpButton.png";
        std::string selectedPicPath = "SelectedLevelUpButton.png";
        std::string disabledPicPath = "DisabledLevelUpButton.png";
        buttonLevelUp = Button::create(normalPicPath, selectedPicPath, disabledPicPath);
        std::string words = ConfigController::getInstance()->getCNByID(WORDS_LEVELUP);
        buttonLevelUp->setTitleText(words);
        buttonLevelUp->setTitleFontName("fonts/simkai.ttf");
        buttonLevelUp->setTitleFontSize(24.0f);
        buttonLevelUp->setTitleColor(Color3B::BLACK);
        setButtonPosition(buttonLevelUp, Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.75f), 2);

        CTGScene::getLayer()->addChild(buttonLevelUp);

        buttonLevelUp->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
            switch (type) {
            case ui::Widget::TouchEventType::ENDED:
                if (money - MONEY_ADD_EXP >= 0) {
                    money -= MONEY_ADD_EXP;
                    expr += EXP_ADD_ONCE;
                    transformExpToLevel();
                    updateButtonState();
                    updateLevelLabel();
                    updateMoneyLabel();
                }
                break;
            default:
                break;
            }
            });
    }

    void createRefreshShopButton() {
        // 创建刷新商店按钮的逻辑
    }

    void createLabelsAndSprites() {
        // 创建标签和精灵的逻辑
    }

    void initAllChessPrice() {
        int price = 1;
        for (int i = 1; i <= NUM_CHESS; i++) {
            allChessPrice[i] = price;
            if (i == 5 || i == 8) {
                price++;
            }
        }
    }

    void getChessPrice() {
        std::copy(std::begin(allChessPrice), std::end(allChessPrice), std::begin(chessPrice));
    }

    void createChessButton(int numOfChess, int index) {
        assert(numOfChess >= 1 && numOfChess <= NUM_CHESS_SHOP);
        assert(index >= 1 && index <= NUM_CHESS);

        // 创建按钮的逻辑
    }

    void createInitialChessButtons() {
        std::default_random_engine randomEngine;
        std::uniform_int_distribution<int> u1(1, 100);
        std::uniform_int_distribution<int> u2(1, 100);
        randomEngine.seed(time(0));

        for (int num = 1; num <= NUM_CHESS_SHOP; num++) {
            int r1 = u1(randomEngine);
            int r2 = getChessIndexByLevel(r1);
            createChessButton(num, r2);
            CTGScene::getLayer()->addChild(chessButton[num]);
            setButtonPosition(chessButton[num], getChessPosition(num));
        }
    }

    int getChessIndexByLevel(int r) {
        const int lim1 = 60 - 5 * level;
        const int lim2 = 105 - 5 * level;

        if (r <= lim1) {
            return (std::rand() % 5 + 1);
        }
        else if (r > lim1 && r <= lim2) {
            return (std::rand() % 3 + 6);
        }
        else {
            return (std::rand() % 2 + 9);
        }
    }

    void updateButtonState() {
        // 更新按钮禁用状态的逻辑
    }

    void updateLevelLabel() {
        // 更新等级标签的逻辑
    }

    void updateMoneyLabel() {
        // 更新金币标签的逻辑
    }

    void setButtonPosition(Button* button, const Vec2& position, int zOrder = 0) {
        button->setPosition(origin + position);
        button->setLocalZOrder(zOrder);
    }
};

/****************************************************
 * 功能：开始的卡牌按钮
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void Shop::createInitialChessButton()
{
    // 产生随机数种子
    std::default_random_engine randomEngine;
    std::uniform_int_distribution<int> u1(1, 100);  // 模拟随机
    std::uniform_int_distribution<int> u2(1, 100);  // 真实下标
    randomEngine.seed(time(0));

    // 初始化商店
    for (int num = 1; num <= NUM_CHESS_SHOP; num++)
    {
        // 产生随机数
        int r1 = u1(randomEngine);
        int r2 = 1;

        // 根据等级调整概率
        const int lim1 = 60 - 5 * level;
        const int lim2 = 105 - 5 * level;

        // 产生编号
        if (r1 <= lim1)
            r2 = (u2(randomEngine) % 5 + 1);    // 前5个是1费
        else if (r1 > lim1 && r1 <= lim2)
            r2 = (u2(randomEngine) % 3 + 6);    // 6~8是2费
        else
            r2 = (u2(randomEngine) % 2 + 9);    // 9~10是3费

        // 创建并加入场景中
        createChessButton(num, r2);
        CTGScene::getLayer()->addChild(chessButton[num], 2);    // z 值为 2

        // 显示按钮
        auto chessPosition = Shop::getChessPosition(num);
        chessButton[num]->setPosition(chessPosition);	// 设置位置
    }
}

/****************************************************
 * 功能：升级按钮 z 值为 3
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void Shop::createLevelUpButton()
{
    std::string normalPicPath = "NormalLevelUpButton.png";	// 未被选中时按钮样式
    std::string selectedPicPath = "SelectedLevelUpButton.png";	// 被选中时按钮样式
    std::string disabledPicPath = "DisabledLevelUpButton.png";  // 被禁用时按钮样式
    buttonLevelUp = Button::create(normalPicPath, selectedPicPath, disabledPicPath);// 创建按钮
    std::string words = ConfigController::getInstance()->getCNByID(WORDS_LEVELUP);	// 获取中文“升级”
    buttonLevelUp->setTitleText(words);						// 设置按钮文字
    buttonLevelUp->setTitleFontName("fonts/simkai.ttf");	// 设置字体
    buttonLevelUp->setTitleFontSize(24.0f);					// 设置字号
    buttonLevelUp->setTitleColor(Color3B::BLACK);			// 设置颜色
    buttonLevelUp->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.75f));	// 设置位置

    CTGScene::getLayer()->addChild(buttonLevelUp, 3);						// 按钮 z 值为 3

    // 使用lambda表达式，引用方式捕获外部变量
    buttonLevelUp->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)  // 回调函数
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (money - MONEY_ADD_EXP >= 0)     // 如果钱够，就升级
                {
                    money -= MONEY_ADD_EXP; // 花费金币
                    expr += EXP_ADD_ONCE;   // 加经验
                    transformExpToLevel();  // 转化为等级

                    // 更新按钮禁用状态
                    updateButtonState();

                    updateLevelLabel();
                    updateMoneyLabel();  // 更新标签

                    // 根据等级增加可上场英雄数
                }
                break;
            default:
                break;
            }
        });
}

/****************************************************
 * 功能：刷新商店按钮 z 值为 3
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void Shop::createRefreshShopButton()
{
    std::string normalPicPath = "NormalRefreshShopButton.png";		// 未被选中时按钮样式
    std::string selectedPicPath = "SelectedRefreshShopButton.png";	// 被选中时按钮样式
    std::string disabledPicPath = "DisabledRefreshShopButton.png";  // 被禁用时按钮样式
    buttonRefreshShop = Button::create(normalPicPath, selectedPicPath, disabledPicPath);    // 创建按钮
    std::string words = ConfigController::getInstance()->getCNByID(WORDS_REFRESH);	// 获取中文“刷新”
    buttonRefreshShop->setTitleText(words);						// 设置按钮文字
    buttonRefreshShop->setTitleFontName("fonts/simkai.ttf");	// 设置字体
    buttonRefreshShop->setTitleFontSize(24.0f);					// 设置字号
    buttonRefreshShop->setTitleColor(Color3B::BLACK);			// 设置颜色
    buttonRefreshShop->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.25f));	// 设置位置

    CTGScene::getLayer()->addChild(buttonRefreshShop, 3);						// 按钮 z 值为 3

    // 使用lambda表达式，引用方式捕获外部变量
    buttonRefreshShop->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)  // 回调函数
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (money - REFRESH_ONCE >= 0)
                {
                    money -= REFRESH_ONCE;   // 花费金币
                    // 根据等级刷新商店
                    refreshShop();

                    // 更新价格
                    getChessPrice();

                    // 更新按钮禁用状态
                    updateButtonState();

                    updateMoneyLabel();     // 更新标签
                }
                break;
            default:
                break;
            }
        });
}

/****************************************************
 * 功能：经验值标签
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void Shop::createLevelLabel()
{
    const std::string backgroundPicPath = "LevelLabelBackGround.png";
    spriteLevelLabel = Sprite::create(backgroundPicPath);
    spriteLevelLabel->setPosition(origin + Vec2(visibleSize.width * 0.925f, SHOP_HEIGHT * 0.75f));
    CTGScene::getLayer()->addChild(spriteLevelLabel, 2);

    // 使用 stringstream 格式化输出
    std::stringstream words;
    words << "    " << level << words_level_1 << "\n" << words_level_2 << std::setw(2) << std::setfill('0') << expr << "/"
        << std::setw(2) << EXP_LEVEL[level + 1];
    labelLevel = Label::createWithTTF(words.str(), "fonts/simkai.ttf", 24.0f);
    labelLevel->setPosition(spriteLevelLabel->getPosition());
    labelLevel->setTextColor(Color4B::BLACK);
    CTGScene::getLayer()->addChild(labelLevel, 3);
}

/****************************************************

功能：金币标签
作者：黄辰宇
时间：2023年12月23日
CopyRight 2023 by 黄辰宇

**************************************************/
void Shop::createMoneyLabel()
{
    const std::string backgroundPicPath = "MoneyLabelBackGround.png";
    spriteMoneyLabel = Sprite::create(backgroundPicPath);
    spriteMoneyLabel->setPosition(origin + Vec2(visibleSize.width * 0.925f, SHOP_HEIGHT * 0.25f));
    CTGScene::getLayer()->addChild(spriteMoneyLabel, 2);

    // 使用 stringstream 格式化输出
    std::stringstream words;
    words << words_money << std::setw(3) << std::setfill('0') << money;
    labelMoney = Label::createWithTTF(words.str(), "fonts/simkai.ttf", 32.0f);
    labelMoney->setPosition(spriteMoneyLabel->getPosition());
    labelMoney->setTextColor(Color4B::BLACK);
    CTGScene::getLayer()->addChild(labelMoney, 3);
}

/****************************************************

功能：创建出售区域
作者：黄辰宇
时间：2023年12月27日
CopyRight 2023 by 黄辰宇

**************************************************/
void Shop::createSellSprite()
{
    const std::string sellSpritePicPath = "SellOrigin.png";
    spriteSellOrigin = Sprite::create(sellSpritePicPath);
    spriteSellOrigin->setPosition(origin + Vec2(visibleSize.width * 0.925f, visibleSize.height * 0.925f));
    spriteSellOrigin->setOpacity(80);
    CTGScene::getLayer()->addChild(spriteSellOrigin, 2);

    const std::string words = ConfigController::getInstance()->getCNByID(WORDS_SELL);
    labelSellOrigin = Label::createWithTTF(words, "fonts/simkai.ttf", 32.0f);
    labelSellOrigin->setPosition(spriteSellOrigin->getPosition());
    labelSellOrigin->setTextColor(Color4B::BLACK);
    CTGScene::getLayer()->addChild(labelSellOrigin, 3);
}

/****************************************************

功能：获取从左到右第numofChess张卡牌中心位置
参数：从左到右第几张卡牌，注意不要超过NUM_CHESS_SHOP
作者：黄辰宇
时间：2023年12月22日
CopyRight 2023 by 黄辰宇

**************************************************/
Vec2 Shop::getChessPosition(const int numofChess)
{
    if (numofChess > NUM_CHESS_SHOP)
    {
        // 日志可以通过重定向查看
        CCLOG("第%d张卡牌超过商店卡牌总数%d，位置给出错误（Shop.cpp）\n", numofChess, NUM_CHESS_SHOP);
        return Vec2::ZERO;
    }

    const float chessMiddle_x = shopStart_x + (numofChess - 1) * chessWidth + chessWidth / 2.0f;
    const Vec2 position = origin + Vec2(chessMiddle_x, SHOP_HEIGHT / 2.0f);

    return position;
}

/****************************************************
 * 功能：更新等级标签
 * 作者：黄辰宇
 * 时间：2023年12月28日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void Shop::updateLevelLabel()
{
    std::string words = "";

    // 标签文字如 
    //               2级
    //            当前：4/10
    std::string words_1 = std::to_string(level);
    std::string words_2 = std::to_string(expr);
    std::string words_3 = std::to_string(EXP_LEVEL[level + 1]);

    words = "    " + words_1 + words_level_1 + "\n" + words_level_2 + words_2 + "/" + words_3;

    labelLevel->setString(words);
}

/****************************************************
 * 功能：更新金币标签
 * 作者：黄辰宇
 * 时间：2023年12月28日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void Shop::updateMoneyLabel()
{
    std::string words = "";

    // 标签文字如 
    //               金币：10
    std::string words_1 = std::to_string(money);

    words = words_money + words_1;

    labelMoney->setString(words);
}

/****************************************************
 * 功能：更新按钮禁用状态（不能用在回调函数中？！）
 * 注意：每次花钱以后都要进行更新
 * 作者：黄辰宇
 * 时间：2023年12月24日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void Shop::updateButtonState()
{
    if (buttonLevelUp == nullptr || buttonRefreshShop == nullptr)
        return;

    // 升级按钮
    buttonLevelUp->setEnabled(!(level == MAX_LEVEL || money - EXP_ADD_ONCE < 0));

    // 刷新商店按钮
    buttonRefreshShop->setEnabled(money - REFRESH_ONCE >= 0);

    // 卡牌按钮
    for (int i = 1; i <= NUM_CHESS_SHOP; i++)   // 看看哪个英雄买不起
    {
        if (chessButton[i] != nullptr)
            chessButton[i]->setEnabled(money - chessPrice[i] >= 0);
    }
}

/****************************************************
 * 功能：将经验转化为等级
 * 作者：黄辰宇
 * 时间：2023年12月24日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void Shop::transformExpToLevel()
{
    for (int lev = MAX_LEVEL; lev >= level + 1; lev--)
    {
        if (expr >= EXP_LEVEL[lev])
        {
            level = lev;
            expr -= EXP_LEVEL[lev];
            break;
        }
    }
}

/****************************************************
 * 功能：根据等级刷新商店
 * 注意：只能在商店已有卡牌的情况下刷新，另外刷新的同时会
 *      从层中移除结点
 * 作者：黄辰宇
 * 时间：2023年12月24日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
void Shop::refreshShop()
{
    if (chessButton == nullptr)
    {
        CCLOG("初始化时不能使用刷新商店函数！(shop.cpp)");
        return;
    }

    // 产生随机数种子
    std::default_random_engine randomEngine(time(0));
    std::uniform_int_distribution<int> u1(1, 100);  // 模拟随机
    std::uniform_int_distribution<int> u2(1, 100);  // 真实下标

    // 刷新商店
    for (int num = 1; num <= NUM_CHESS_SHOP; num++)
    {
        // 产生随机数
        int r1 = u1(randomEngine);
        int r2 = 1;

        // 根据等级调整概率
        const int lim1 = 60 - 5 * level;
        const int lim2 = 105 - 5 * level;

        // 产生编号
        if (r1 <= lim1)
            r2 = (u2(randomEngine) % 5 + 1);    // 前5个是1费
        else if (r1 > lim1 && r1 <= lim2)
            r2 = (u2(randomEngine) % 3 + 6);    // 6~8是2费
        else
            r2 = (u2(randomEngine) % 2 + 9);    // 9~10是3费

        // 移除原按钮（先移除再更新！！）
        if (chessButton[num] != nullptr)
        {
            chessButton[num]->removeFromParentAndCleanup(true);
            chessButton[num] = nullptr;
        }

        // 更新商店卡牌和卡牌按钮并加入场景中
        createChessButton(num, r2);
        CTGScene::getLayer()->addChild(chessButton[num], 2);    // z 值为 2

        // 根据更新后的数组创建按钮
        auto chessPosition = Shop::getChessPosition(num);
        chessButton[num]->setPosition(chessPosition);	// 设置位置
    }
}

/****************************************************
 * 功能：获取编号为idx的英雄价格
 * 作者：黄辰宇
 * 时间：2023年12月24日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
int Shop::getHeroPrice(int idxOfHero)
{
    if (idxOfHero <= 0 || idxOfHero > NUM_CHESS)
    {
        CCLOG("英雄编号越界，获取价格失败!\n");
        return -1;
    }
    return allChessPrice[idxOfHero];
}