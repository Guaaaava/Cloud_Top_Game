#include"Hero.h"

bool Hero::init(Vec2& start_pos )
{
	if (!Sprite::init())return false;
	return true;
}


/****************************************************
 * ���ܣ�Samurai���Ա����
 * ���ߣ���˼��
 ****************************************************/
bool Samurai::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	return true;
}

Animation* Samurai::createPlistAnimation(std::string filename,std::string framename,int photonums)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
	_sprite = Sprite::createWithSpriteFrameName("1"+framename);
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


//void Samurai::heroRun(Vec2&end_pos)
//{
//	//ͨ��plist�ļ�����֡����
//	_run=createPlistAnimation("Samurai/Samurai_Run.plist", "_Samurai_Run",8);
//	auto animate = Animate::create (_run);
//	_sprite->runAction(RepeatForever::create(animate)); // ������ͣ����
//	// �����ƶ�����
//	MoveTo* moveTo = MoveTo::create(3, end_pos); // ʱ�䡢Ŀ��λ��
//	_sprite->runAction(moveTo);
//	_postion = end_pos;//����Ӣ������
//}

void Samurai::heroAttack()
{

	//ͨ��plist�ļ�����֡����
	_attack=createPlistAnimation("Samurai/Samurai_Attack.plist","_Samurai_Attack", 4);
	auto animate = Animate::create(_attack);
	auto animateforever = RepeatForever::create(animate);
	_sprite->runAction(animateforever);//������ͣ����
}
void Samurai::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead=createPlistAnimation("Samurai/Samurai_Dead.plist", "_Samurai_Dead", 6);
	
	auto animate = Animate::create(_dead);
	_sprite->runAction(animate);
}

void Samurai::heroRunAndAttack(Vec2& end_pos)
{
    // ͨ��plist�ļ�����֡����
    _run = createPlistAnimation("Samurai/Samurai_Run.plist", "_Samurai_Run", 8);
    auto runAnimate = Animate::create(_run);
    auto runAction = RepeatForever::create(runAnimate);
    _sprite->runAction(runAction); // �����ܲ�����

    // �����ƶ�����
    MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
    auto moveCallback = CallFunc::create([this]() {
        _sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
        heroAttack(); // ���Ź�������
    });
    auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
    _sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�Knight���Ա����
 * ���ߣ���˼��
 ****************************************************/
bool Knight::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;
	return true;
}

Animation* Knight::createPlistAnimation(std::string filename, std::string framename, int photonums)
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

//void Knight::heroRun(Vec2& end_pos)
//{
//	//ͨ��plist�ļ�����֡����
//	_run = createPlistAnimation("Knight/Knight_Run.plist", "_Knight_Run", 7);
//	auto animate = Animate::create(_run);
//	_sprite->runAction(RepeatForever::create(animate)); // ������ͣ����
//	// �����ƶ�����
//	MoveBy* moveBy = MoveBy::create(3, end_pos); // ʱ�䡢λ������
//	_sprite->runAction(moveBy); // ��ʼ�ƶ���ֹͣ���������ж���
//	_postion = end_pos;//����Ӣ������
//}
void Knight::heroAttack()
{
	//ͨ��plist�ļ�����֡����
	_attack=createPlistAnimation("Knight/Knight_Attack.plist","_Knight_Attack",4);
	auto animate = Animate::create(_attack);
	auto animateforever = RepeatForever::create(animate);
	_sprite->runAction(animateforever->clone());//������ͣ����
	//sprite->runAction(Sequence::createWithTwoActions(
	//	Repeat::create(animate, 3),
	//	CallFunc::create([sprite]() {sprite->removeFromParent();
	//		})
	//));

}

void Knight::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead=createPlistAnimation("Knight/Knight_Dead.plist", "_Knight_Dead", 6);

	auto animate = Animate::create(_dead);
	_sprite->runAction(animate);
}

void Knight::heroRunAndAttack(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("Knight/Knight_Run.plist", "_Knight_Run", 7);
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����
	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAttack(); // ���Ź�������
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}

/****************************************************
 * ���ܣ�Kunoichi���Ա����
 * ���ߣ���˼��
 ****************************************************/
bool Kunoichi::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;

	return true;
}
Animation* Kunoichi::createPlistAnimation(std::string filename, std::string framename, int photonums)
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


void Kunoichi::heroAttack()
{

	//ͨ��plist�ļ�����֡����
	_attack = createPlistAnimation("Kunoichi/Kunoichi_Attack.plist", "_Kunoichi_Attack", 6);
	auto animate = Animate::create(_attack);
	auto animateforever = RepeatForever::create(animate);
	_sprite->runAction(animateforever);//������ͣ����
}
void Kunoichi::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("Kunoichi/Kunoichi_Dead.plist", "_Kunoichi_Dead", 5);

	auto animate = Animate::create(_dead);
	_sprite->runAction(animate);
}

void Kunoichi::heroRunAndAttack(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("Kunoichi/Kunoichi_Run.plist", "_Kunoichi_Run", 8);
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAttack(); // ���Ź�������
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}
/****************************************************
 * ���ܣ�LightningMage���Ա����
 * ���ߣ���˼��
 ****************************************************/
bool LightningMage::init(Vec2& start_pos)
{
	if (!Sprite::init())return false;
	_postion = start_pos;

	return true;
}
Animation* LightningMage::createPlistAnimation(std::string filename, std::string framename, int photonums)
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


void LightningMage::heroAttack()
{

	//ͨ��plist�ļ�����֡����
	_attack = createPlistAnimation("LightningMage/LightningMage_Attack.plist", "_LightningMage_Attack", 4);
	auto animate = Animate::create(_attack);
	auto animateforever = RepeatForever::create(animate);
	_sprite->runAction(animateforever);//������ͣ����
}
void LightningMage::heroDead()
{
	//ͨ��plist�ļ�����֡����
	_dead = createPlistAnimation("LightningMage/LightningMage_Dead.plist", "_LightningMage_Dead", 5);

	auto animate = Animate::create(_dead);
	_sprite->runAction(animate);
}

void LightningMage::heroRunAndAttack(Vec2& end_pos)
{
	// ͨ��plist�ļ�����֡����
	_run = createPlistAnimation("LightningMage/LightningMage_Run.plist", "_LightningMage_Run", 8);
	auto runAnimate = Animate::create(_run);
	auto runAction = RepeatForever::create(runAnimate);
	_sprite->runAction(runAction); // �����ܲ�����

	// �����ƶ�����
	MoveTo* moveTo = MoveTo::create(3, end_pos); // �ƶ���Ŀ��λ��
	_postion = end_pos;//����Ӣ������
	auto moveCallback = CallFunc::create([this]() {
		_sprite->stopAllActions(); // ֹͣ�ܲ�����
		_sprite->setVisible(false); // ���ؾ���
		heroAttack(); // ���Ź�������
		});
	auto sequence = Sequence::create(moveTo, moveCallback, nullptr);
	_sprite->runAction(sequence);
}