#pragma once

#include <string>
#include <map>

#include "cocos2d.h"
USING_NS_CC;			// 相当于 using namespace cocos2d;

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

private:
	static ConfigController* instance;

	// 记录文字表（缓存数据）
	std::map<int, Value> prt_cnWords;
};

