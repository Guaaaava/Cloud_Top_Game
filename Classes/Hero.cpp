#include "Hero.h"
/**************
* ����:Ӣ����(������)
* ����:�����
* ʱ��:2023��12��29��
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
