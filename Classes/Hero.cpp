#include "Hero.h"
/**************
* 功能:英雄类(测试用)
* 作者:尹泽河
* 时间:2023年12月29日
**************/

bool Hero::init()
{
	if (!Sprite::init()) {
		return false;
	}

	return true;
}

bool Annie::init()
{
	if (!Hero::init()) {
		return false;
	}

	this->setTexture("HelloWorld.png");

	return true;
}
