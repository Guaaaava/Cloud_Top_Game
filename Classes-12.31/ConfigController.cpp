#include "ConfigController.h"

/****************************************************
 * 功能：配置文件控制器默认函数
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
ConfigController* ConfigController::instance = nullptr;
ConfigController* ConfigController::getInstance()
{
	if (instance == nullptr)
	{
		instance = new ConfigController();
	}
	return instance;
}
void ConfigController::destroyInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
ConfigController::~ConfigController()
{
	prt_cnWords.clear();
	prt_picPath.clear();
	ConfigController::destroyInstance();
}

/****************************************************
 * 功能：通过编号获取指定文字
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
std::string ConfigController::getCNByID(int id)
{
	// 如果缓存为空，读取配置文件；不为空则不需要读取
	if (prt_cnWords.empty())
	{
		// 读取中文字plist配置文件，防止出现乱码
		auto data = FileUtils::getInstance()->getValueMapFromFile("res/CNWords.plist");
		for (auto mapPair : data)
		{
			int key = Value(mapPair.first).asInt();		// 转为 int
			Value val = mapPair.second;

			prt_cnWords.insert(std::pair<int, Value>(key, val));
		}
	}

	if (prt_cnWords.empty())
	{
		return "";
	}

	return prt_cnWords.at(id).asString();		// 转为 string
}

/****************************************************
 * 功能：通过编号获取指定文字
 * 作者：黄辰宇
 * 时间：2023年12月23日
 * **************************************************
 * CopyRight 2023 by 黄辰宇
 * **************************************************/
std::string ConfigController::getPathByID(int id)
{
	// 如果缓存为空，读取配置文件；不为空则不需要读取
	if (prt_picPath.empty())
	{
		// 读取图片路径plist配置文件
		auto data = FileUtils::getInstance()->getValueMapFromFile("res/PicPath.plist");
		for (auto mapPair : data)
		{
			int key = Value(mapPair.first).asInt();		// 转为 int
			Value val = mapPair.second;

			prt_picPath.insert(std::pair<int, Value>(key, val));
		}
	}

	if (prt_picPath.empty())
	{
		return "";
	}

	return prt_picPath.at(id).asString();		// 转为 string
}