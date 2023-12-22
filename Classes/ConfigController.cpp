#include "ConfigController.h"

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
}

std::string ConfigController::getCNByID(int id)
{
	// 如果缓存为空，读取配置文件；不为空则不需要读取
	if (prt_cnWords.empty())
	{
		// 读取中文字plist配置文件，防止出现乱码
		auto data = FileUtils::getInstance()->getValueMapFromFile("res/tips.plist");
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
