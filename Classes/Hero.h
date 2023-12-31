#pragma once
#include<list>
#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class Hero :public Sprite
{
public:
	//Ӣ��ѡ���������߼�
	void heroAction();
	//��lv��
	void upLevel(int lv) { _lv += lv; _hp *= _lv; _ap *= _lv;  _max_hp = _hp; };
	//ÿ�غϼ��ٵ�Ѫ��
	void getHurted() {
		for (std::list<Hero*>::iterator iter = _l.begin(); iter != _l.end(); iter++)
		{
			if ((*iter)->_hp > 0)
			{
				if ((*iter)->_mp >= (*iter)->_max_mp)
					_enemy_ap += (*iter)->_skill_ap;
				else
					_enemy_ap += (*iter)->_ap;
			}
		}
		_hp -= _enemy_ap;
	};
	//��ȡ������Ϣ
	void getEnemyInfor(std::list<Hero*>l) { _l = l; };
	//����plist֡����
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	//��ʼ���������ԣ��Լ�����start_pos��Ĭ������Ϊ��Ļ���룩
	virtual bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2)) = 0;
	//ǰ���������겢ִ�н�������һϵ�ж���
	virtual void heroRunToEnemyPos(Vec2& end_pos) = 0;
	//ʵ��Ӣ�۹�������
	virtual void heroAttack() = 0;
	//ʵ��Ӣ����������
	virtual void heroDead() = 0;
	//�ƶ���ĳһ�㲢����
	virtual void heroSkill() = 0;
	// ����ͷ��Ѫ��
	void createHealthBar();
	// ����ͷ��Ѫ��λ��
	void updateHealthBarPosition();
	// ����ͷ��Ѫ����ʾ
	//void updateHealthBarDisplay();
	void updateHealthBar(float dt);
	// ����ͷ������
	void createMagicBar();
	// ����ͷ������λ��
	void updateMagicBarPosition();
	// ����ͷ��������ʾ
	void updateMagicBar(float dt);

protected:
	double _enemy_ap = 0;
	bool _reverse = false;//�ƶ�ʱ�Ƿ�ת
	Vec2 _postion;//��ǰλ��
	double _hp;
	double _ap;
	double _mp;
	int _lv;
	double _max_mp;
	double _skill_ap;
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Animation* _skill;
	std::list<Hero*>_l;
	ProgressTimer* _healthBar;  // ͷ��Ѫ��
	ProgressTimer* _magicBar;  // ͷ������
	double _max_hp;
};

class Samurai :public Hero
{
public:
	CREATE_FUNC(Samurai);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
	
};

class Knight :public Hero
{
public:
	CREATE_FUNC(Knight);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};
class Berserker :public Hero
{
public:
	CREATE_FUNC(Berserker);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};

class Kunoichi :public Hero
{
public:
	CREATE_FUNC(Kunoichi);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void getHurted(int enemy_ap);
	void heroSkill();

};

class LightningMage :public Hero
{
public:
	CREATE_FUNC(LightningMage);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	/*void heroRun(Vec2& end_pos);*/
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};

class FireVizard :public Hero
{
public:
	CREATE_FUNC(FireVizard);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};

class WandererMagican :public Hero
{
public:
	CREATE_FUNC(WandererMagican);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();


};
class NinjaMonk :public Hero
{
public:
	CREATE_FUNC(NinjaMonk);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};
class NinjaPeasant :public Hero
{
public:
	CREATE_FUNC(NinjaPeasant);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};
class SamuraiCommander :public Hero
{
public:
	CREATE_FUNC(SamuraiCommander);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();

};