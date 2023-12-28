#pragma once

#include <string>
#include <map>

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;

// 中文字编码
#define WORDS_GAME_NAME 1001	// “金铲铲之战”编码
#define WORDS_GAME_START 1002	//“开始游戏”编码
#define WORDS_GAME_CLOSE 1003	//“退出游戏”编码
#define WORDS_TRAINING_MODE 1004//“训练模式”编码
#define WORDS_ONLINE_MODE 1005	//“联机模式”编码
#define WORDS_MUSIC_VOLUME 1006 //“音量大小”编码
#define WORDS_IMAGE_QULITY 1007 //“画质”编码
#define WORDS_IMAGE_LOW 1008	//“低”编码
#define WORDS_IMAGE_MID 1009	//“中”编码
#define WORDS_IMAGE_HIG 1010	//“高”编码
#define WORDS_LEVELUP	2001	// “升级”编码
#define WORDS_REFRESH	2002	// "刷新”编码
#define WORDS_LEVEL_1	2003	// “级”编码
#define WORDS_LEVEL_2	2004	// "经验："编码
#define WORDS_MONEY		2005	// "金币："编码
#define WORDS_SELL		2006	// “出售”编码

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
