#pragma once

#include <string>
#include <map>

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;

// 中文字编码
#define WORDS_GAME_NAME 1001	// “金铲铲之战”编码
#define WORDS_START     1002	// “开始”编码
#define WORDS_SHOP      1003	// “商店”编码
#define WORDS_EXIT      1004	// “退出”编码
#define WORDS_LEVELUP	1005	// “升级”编码
#define WORDS_REFRESH	1006	// "刷新”编码
#define WORDS_LEVEL_1	1007	// “级”编码
#define WORDS_LEVEL_2	1008	// "经验："编码
#define WORDS_MONEY		1009	// "金币："编码
#define WORDS_SELL		1010	// “出售”编码

// 图片路径编码，下标从1开始
const int MAX_NUM_KEY = 10;
const int PATH_NORMAL[MAX_NUM_KEY + 5] = { 0x3f3f3f3f, 1,2,3,4,5,6,7,8,9,10 };
const int PATH_SELECTED[MAX_NUM_KEY + 5] = { -0x3f3f3f3f, -1,-2,-3,-4,-5,-6,-7,-8,-9,-10 };
const int PATH_DISABLED[MAX_NUM_KEY + 5] = { 0x3f3f3f3f, -111, -222, -333, -444, -555, -666, -777, -888, -999, -101010 };

/****************************************************
 * 功能：配置文件控制器，实现读取和缓存配置文件数据
 * 作者：黄辰宇
 * 时间：2023年12月7日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
class ConfigController
{
public:
	static ConfigController* getInstance();
	static void destroyInstance();
	~ConfigController();

	// 通过编号获取指定文字
	std::string getCNByID(int id);

	// 通过编号获取牌库图片路径
	std::string getPathByID(int id);

private:
	static ConfigController* instance;

	// 记录文字表（缓存数据）
	std::map<int, Value> prt_cnWords;

	// 记录牌库图片路径
	std::map<int, Value> prt_picPath;
};

