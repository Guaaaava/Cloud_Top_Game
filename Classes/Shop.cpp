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
        // ����ˢ���̵갴ť���߼�
    }

    void createLabelsAndSprites() {
        // ������ǩ�;�����߼�
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

        // ������ť���߼�
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
        // ���°�ť����״̬���߼�
    }

    void updateLevelLabel() {
        // ���µȼ���ǩ���߼�
    }

    void updateMoneyLabel() {
        // ���½�ұ�ǩ���߼�
    }

    void setButtonPosition(Button* button, const Vec2& position, int zOrder = 0) {
        button->setPosition(origin + position);
        button->setLocalZOrder(zOrder);
    }
};

/****************************************************
 * ���ܣ���ʼ�Ŀ��ư�ť
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createInitialChessButton()
{
    // �������������
    std::default_random_engine randomEngine;
    std::uniform_int_distribution<int> u1(1, 100);  // ģ�����
    std::uniform_int_distribution<int> u2(1, 100);  // ��ʵ�±�
    randomEngine.seed(time(0));

    // ��ʼ���̵�
    for (int num = 1; num <= NUM_CHESS_SHOP; num++)
    {
        // ���������
        int r1 = u1(randomEngine);
        int r2 = 1;

        // ���ݵȼ���������
        const int lim1 = 60 - 5 * level;
        const int lim2 = 105 - 5 * level;

        // �������
        if (r1 <= lim1)
            r2 = (u2(randomEngine) % 5 + 1);    // ǰ5����1��
        else if (r1 > lim1 && r1 <= lim2)
            r2 = (u2(randomEngine) % 3 + 6);    // 6~8��2��
        else
            r2 = (u2(randomEngine) % 2 + 9);    // 9~10��3��

        // ���������볡����
        createChessButton(num, r2);
        CTGScene::getLayer()->addChild(chessButton[num], 2);    // z ֵΪ 2

        // ��ʾ��ť
        auto chessPosition = Shop::getChessPosition(num);
        chessButton[num]->setPosition(chessPosition);	// ����λ��
    }
}

/****************************************************
 * ���ܣ�������ť z ֵΪ 3
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createLevelUpButton()
{
    std::string normalPicPath = "NormalLevelUpButton.png";	// δ��ѡ��ʱ��ť��ʽ
    std::string selectedPicPath = "SelectedLevelUpButton.png";	// ��ѡ��ʱ��ť��ʽ
    std::string disabledPicPath = "DisabledLevelUpButton.png";  // ������ʱ��ť��ʽ
    buttonLevelUp = Button::create(normalPicPath, selectedPicPath, disabledPicPath);// ������ť
    std::string words = ConfigController::getInstance()->getCNByID(WORDS_LEVELUP);	// ��ȡ���ġ�������
    buttonLevelUp->setTitleText(words);						// ���ð�ť����
    buttonLevelUp->setTitleFontName("fonts/simkai.ttf");	// ��������
    buttonLevelUp->setTitleFontSize(24.0f);					// �����ֺ�
    buttonLevelUp->setTitleColor(Color3B::BLACK);			// ������ɫ
    buttonLevelUp->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.75f));	// ����λ��

    CTGScene::getLayer()->addChild(buttonLevelUp, 3);						// ��ť z ֵΪ 3

    // ʹ��lambda���ʽ�����÷�ʽ�����ⲿ����
    buttonLevelUp->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)  // �ص�����
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (money - MONEY_ADD_EXP >= 0)     // ���Ǯ����������
                {
                    money -= MONEY_ADD_EXP; // ���ѽ��
                    expr += EXP_ADD_ONCE;   // �Ӿ���
                    transformExpToLevel();  // ת��Ϊ�ȼ�

                    // ���°�ť����״̬
                    updateButtonState();

                    updateLevelLabel();
                    updateMoneyLabel();  // ���±�ǩ

                    // ���ݵȼ����ӿ��ϳ�Ӣ����
                }
                break;
            default:
                break;
            }
        });
}

/****************************************************
 * ���ܣ�ˢ���̵갴ť z ֵΪ 3
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createRefreshShopButton()
{
    std::string normalPicPath = "NormalRefreshShopButton.png";		// δ��ѡ��ʱ��ť��ʽ
    std::string selectedPicPath = "SelectedRefreshShopButton.png";	// ��ѡ��ʱ��ť��ʽ
    std::string disabledPicPath = "DisabledRefreshShopButton.png";  // ������ʱ��ť��ʽ
    buttonRefreshShop = Button::create(normalPicPath, selectedPicPath, disabledPicPath);    // ������ť
    std::string words = ConfigController::getInstance()->getCNByID(WORDS_REFRESH);	// ��ȡ���ġ�ˢ�¡�
    buttonRefreshShop->setTitleText(words);						// ���ð�ť����
    buttonRefreshShop->setTitleFontName("fonts/simkai.ttf");	// ��������
    buttonRefreshShop->setTitleFontSize(24.0f);					// �����ֺ�
    buttonRefreshShop->setTitleColor(Color3B::BLACK);			// ������ɫ
    buttonRefreshShop->setPosition(origin + Vec2(visibleSize.width * 0.075f, SHOP_HEIGHT * 0.25f));	// ����λ��

    CTGScene::getLayer()->addChild(buttonRefreshShop, 3);						// ��ť z ֵΪ 3

    // ʹ��lambda���ʽ�����÷�ʽ�����ⲿ����
    buttonRefreshShop->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)  // �ص�����
        {
            switch (type)
            {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                if (money - REFRESH_ONCE >= 0)
                {
                    money -= REFRESH_ONCE;   // ���ѽ��
                    // ���ݵȼ�ˢ���̵�
                    refreshShop();

                    // ���¼۸�
                    getChessPrice();

                    // ���°�ť����״̬
                    updateButtonState();

                    updateMoneyLabel();     // ���±�ǩ
                }
                break;
            default:
                break;
            }
        });
}

/****************************************************
 * ���ܣ�����ֵ��ǩ
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��23��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::createLevelLabel()
{
    const std::string backgroundPicPath = "LevelLabelBackGround.png";
    spriteLevelLabel = Sprite::create(backgroundPicPath);
    spriteLevelLabel->setPosition(origin + Vec2(visibleSize.width * 0.925f, SHOP_HEIGHT * 0.75f));
    CTGScene::getLayer()->addChild(spriteLevelLabel, 2);

    // ʹ�� stringstream ��ʽ�����
    std::stringstream words;
    words << "    " << level << words_level_1 << "\n" << words_level_2 << std::setw(2) << std::setfill('0') << expr << "/"
        << std::setw(2) << EXP_LEVEL[level + 1];
    labelLevel = Label::createWithTTF(words.str(), "fonts/simkai.ttf", 24.0f);
    labelLevel->setPosition(spriteLevelLabel->getPosition());
    labelLevel->setTextColor(Color4B::BLACK);
    CTGScene::getLayer()->addChild(labelLevel, 3);
}

/****************************************************

���ܣ���ұ�ǩ
���ߣ��Ƴ���
ʱ�䣺2023��12��23��
CopyRight 2023 by �Ƴ���

**************************************************/
void Shop::createMoneyLabel()
{
    const std::string backgroundPicPath = "MoneyLabelBackGround.png";
    spriteMoneyLabel = Sprite::create(backgroundPicPath);
    spriteMoneyLabel->setPosition(origin + Vec2(visibleSize.width * 0.925f, SHOP_HEIGHT * 0.25f));
    CTGScene::getLayer()->addChild(spriteMoneyLabel, 2);

    // ʹ�� stringstream ��ʽ�����
    std::stringstream words;
    words << words_money << std::setw(3) << std::setfill('0') << money;
    labelMoney = Label::createWithTTF(words.str(), "fonts/simkai.ttf", 32.0f);
    labelMoney->setPosition(spriteMoneyLabel->getPosition());
    labelMoney->setTextColor(Color4B::BLACK);
    CTGScene::getLayer()->addChild(labelMoney, 3);
}

/****************************************************

���ܣ�������������
���ߣ��Ƴ���
ʱ�䣺2023��12��27��
CopyRight 2023 by �Ƴ���

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

���ܣ���ȡ�����ҵ�numofChess�ſ�������λ��
�����������ҵڼ��ſ��ƣ�ע�ⲻҪ����NUM_CHESS_SHOP
���ߣ��Ƴ���
ʱ�䣺2023��12��22��
CopyRight 2023 by �Ƴ���

**************************************************/
Vec2 Shop::getChessPosition(const int numofChess)
{
    if (numofChess > NUM_CHESS_SHOP)
    {
        // ��־����ͨ���ض���鿴
        CCLOG("��%d�ſ��Ƴ����̵꿨������%d��λ�ø�������Shop.cpp��\n", numofChess, NUM_CHESS_SHOP);
        return Vec2::ZERO;
    }

    const float chessMiddle_x = shopStart_x + (numofChess - 1) * chessWidth + chessWidth / 2.0f;
    const Vec2 position = origin + Vec2(chessMiddle_x, SHOP_HEIGHT / 2.0f);

    return position;
}

/****************************************************
 * ���ܣ����µȼ���ǩ
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��28��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::updateLevelLabel()
{
    std::string words = "";

    // ��ǩ������ 
    //               2��
    //            ��ǰ��4/10
    std::string words_1 = std::to_string(level);
    std::string words_2 = std::to_string(expr);
    std::string words_3 = std::to_string(EXP_LEVEL[level + 1]);

    words = "    " + words_1 + words_level_1 + "\n" + words_level_2 + words_2 + "/" + words_3;

    labelLevel->setString(words);
}

/****************************************************
 * ���ܣ����½�ұ�ǩ
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��28��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::updateMoneyLabel()
{
    std::string words = "";

    // ��ǩ������ 
    //               ��ң�10
    std::string words_1 = std::to_string(money);

    words = words_money + words_1;

    labelMoney->setString(words);
}

/****************************************************
 * ���ܣ����°�ť����״̬���������ڻص������У�����
 * ע�⣺ÿ�λ�Ǯ�Ժ�Ҫ���и���
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::updateButtonState()
{
    if (buttonLevelUp == nullptr || buttonRefreshShop == nullptr)
        return;

    // ������ť
    buttonLevelUp->setEnabled(!(level == MAX_LEVEL || money - EXP_ADD_ONCE < 0));

    // ˢ���̵갴ť
    buttonRefreshShop->setEnabled(money - REFRESH_ONCE >= 0);

    // ���ư�ť
    for (int i = 1; i <= NUM_CHESS_SHOP; i++)   // �����ĸ�Ӣ������
    {
        if (chessButton[i] != nullptr)
            chessButton[i]->setEnabled(money - chessPrice[i] >= 0);
    }
}

/****************************************************
 * ���ܣ�������ת��Ϊ�ȼ�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
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
 * ���ܣ����ݵȼ�ˢ���̵�
 * ע�⣺ֻ�����̵����п��Ƶ������ˢ�£�����ˢ�µ�ͬʱ��
 *      �Ӳ����Ƴ����
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
void Shop::refreshShop()
{
    if (chessButton == nullptr)
    {
        CCLOG("��ʼ��ʱ����ʹ��ˢ���̵꺯����(shop.cpp)");
        return;
    }

    // �������������
    std::default_random_engine randomEngine(time(0));
    std::uniform_int_distribution<int> u1(1, 100);  // ģ�����
    std::uniform_int_distribution<int> u2(1, 100);  // ��ʵ�±�

    // ˢ���̵�
    for (int num = 1; num <= NUM_CHESS_SHOP; num++)
    {
        // ���������
        int r1 = u1(randomEngine);
        int r2 = 1;

        // ���ݵȼ���������
        const int lim1 = 60 - 5 * level;
        const int lim2 = 105 - 5 * level;

        // �������
        if (r1 <= lim1)
            r2 = (u2(randomEngine) % 5 + 1);    // ǰ5����1��
        else if (r1 > lim1 && r1 <= lim2)
            r2 = (u2(randomEngine) % 3 + 6);    // 6~8��2��
        else
            r2 = (u2(randomEngine) % 2 + 9);    // 9~10��3��

        // �Ƴ�ԭ��ť�����Ƴ��ٸ��£�����
        if (chessButton[num] != nullptr)
        {
            chessButton[num]->removeFromParentAndCleanup(true);
            chessButton[num] = nullptr;
        }

        // �����̵꿨�ƺͿ��ư�ť�����볡����
        createChessButton(num, r2);
        CTGScene::getLayer()->addChild(chessButton[num], 2);    // z ֵΪ 2

        // ���ݸ��º�����鴴����ť
        auto chessPosition = Shop::getChessPosition(num);
        chessButton[num]->setPosition(chessPosition);	// ����λ��
    }
}

/****************************************************
 * ���ܣ���ȡ���Ϊidx��Ӣ�ۼ۸�
 * ���ߣ��Ƴ���
 * ʱ�䣺2023��12��24��
 * **************************************************
 * CopyRight 2023 by �Ƴ���
 * **************************************************/
int Shop::getHeroPrice(int idxOfHero)
{
    if (idxOfHero <= 0 || idxOfHero > NUM_CHESS)
    {
        CCLOG("Ӣ�۱��Խ�磬��ȡ�۸�ʧ��!\n");
        return -1;
    }
    return allChessPrice[idxOfHero];
}