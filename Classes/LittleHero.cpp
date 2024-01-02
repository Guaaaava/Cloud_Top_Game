#include"LittleHero.h"

void LittleHero::initPos(Vec2 start_pos) 
{
	_position = start_pos;
}

Animation* LittleHero::createPlistAnimation(std::string filename, std::string framename, int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	_sprite = Sprite::createWithSpriteFrameName("1" + framename);
	this->addChild(_sprite);
	_sprite->setPosition(_postion);//调整坐标位置;
	auto cache = SpriteFrameCache::getInstance();
	//创建精灵帧集合
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString() + framename));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}


void LittleHero::heroRunToPos(Vec2& end_pos)
{
	// 通过plist文件创建帧动画
	_run = createPlistAnimation("LittleHero/LittleHero_Run.plist", "_LittleHero_Run", 5);
	// 计算英雄移动的方向和距离
	Vec2 direction = end_pos - _position;
	float distance = direction.length();
	direction.normalize();

	// 创建移动动作
	float duration = distance / _speed;
	auto moveTo = MoveTo::create(duration, end_pos);

	// 翻转英雄的朝向
	if (direction.x > 0) {
		_sprite->setFlippedX(false);
	}
	else {
		_sprite->setFlippedX(true);
	}

	// 创建帧动画
	
	auto animate = Animate::create(_run);
	auto repeatAnimate = RepeatForever::create(animate);

	_sprite->runAction(repeatAnimate);
	_sprite->runAction(moveTo);
}