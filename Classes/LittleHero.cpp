#include"LittleHero.h"

bool LittleHero::init(Vec2& start_pos) {
	if (!Sprite::init())return false;
	_position = start_pos;
	_hp = 10;
	_speed = 10;
	return true;
}

Animation* LittleHero::createPlistAnimation(std::string filename, std::string framename, int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	_sprite = Sprite::createWithSpriteFrameName("1" + framename);
	this->addChild(_sprite);
	_sprite->setPosition(_postion);//��������λ��;
	auto cache = SpriteFrameCache::getInstance();
	//��������֡����
	Vector<SpriteFrame*>images;
	for (int i = 1; i <= photonums; i++) {
		images.pushBack(cache->getSpriteFrameByName(Value(i).asString() + framename));
	}
	return Animation::createWithSpriteFrames(images, 1.f / 8);
}


void LittleHero::heroRunToPos(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("LittleHero/LittleHero_Run.plist", "_LittleHero_Run", 5);
	// ����Ӣ���ƶ��ķ���;���
	Vec2 direction = end_pos - _position;
	float distance = direction.length();
	direction.normalize();

	// �����ƶ�����
	float duration = distance / _speed;
	auto moveTo = MoveTo::create(duration, end_pos);

	// ��תӢ�۵ĳ���
	if (direction.x > 0) {
		_sprite->setFlippedX(true);
	}
	else {
		_sprite->setFlippedX(false);
	}

	// ����֡����
	_run = createPlistAnimation("LittleHero/LittleHero_Run.plist", "_LittleHero_Run", 5);
	auto animate = Animate::create(_run);
	auto repeatAnimate = RepeatForever::create(animate);

	// �������ж���
	auto spawn = Spawn::create(moveTo, repeatAnimate, nullptr);

	// ִ���ƶ��Ͷ�������
	_sprite->runAction(spawn);
}