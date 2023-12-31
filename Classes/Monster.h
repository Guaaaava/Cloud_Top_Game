#pragma once
#include<list>
#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class Monster :public Sprite
{
public:
	//Ӣ��ѡ���������߼�
	void monsterAction();
	//��lv��
	void upLevel(int lv) { _lv += lv; _hp *= _lv; _ap *= _lv; };
	//ÿ�غϼ��ٵ�Ѫ��
	void getHurted() {
		for (std::list<Monster*>::iterator iter = _l.begin(); iter != _l.end(); iter++)
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
	void getEnemyInfor(std::list<Monster*>l) { _l = l; };
	//����plist֡����
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);
	//��ʼ���������ԣ��Լ�����start_pos��Ĭ������Ϊ��Ļ���룩
	virtual bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2)) = 0;
	//ǰ���������겢ִ�н�������һϵ�ж���
	virtual void monsterRunToEnemyPos(Vec2& end_pos) = 0;
	//ʵ��Ӣ�۹�������
	virtual void monsterAttack() = 0;
	//ʵ��Ӣ����������
	virtual void monsterDead() = 0;

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
	std::list<Monster*>_l;
};

class BlackWerewolf :public Monster
{
public:
	CREATE_FUNC(BlackWerewolf);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void monsterAttack();
	void monsterDead();
	void monsterRunToEnemyPos(Vec2& end_pos);

};

class SkeletonWarrior :public Monster
{
public:
	CREATE_FUNC(SkeletonWarrior);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void monsterAttack();
	void monsterDead();
	void monsterRunToEnemyPos(Vec2& end_pos);

};
class BlueSlime :public Monster
{
public:
	CREATE_FUNC(BlueSlime);
	bool init(Vec2& start_pos = Vec2(Director::getInstance()->getVisibleSize() / 2));
	void monsterAttack();
	void monsterDead();
	void monsterRunToEnemyPos(Vec2& end_pos);

};
