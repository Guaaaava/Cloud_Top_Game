#pragma once
#include<list>
#include"cocos2d.h"
USING_NS_CC;

#include "ui/UIButton.h"
using namespace ui;

class Hero;

const int ENEMY = 444;
const int PEACE = 555;
const int ME = 666;

/* 整合Hero信息的结构体 */
typedef struct HeroMsg
{
	Hero* hero;
	Sprite* silentSprite;
	int heroTag;
	int heroIdx;
	int level;

	void init(Hero* _hero, Sprite* _sprite, int _tag, int _idx, int _level)
	{
		hero = _hero;
		silentSprite = _sprite;
		heroTag = _tag;
		heroIdx = _idx;
		level = _level;
	};

	bool operator ==(const HeroMsg& item) const
	{
		return (hero == item.hero && silentSprite == item.silentSprite && heroTag == item.heroTag && heroIdx == item.heroIdx && level == item.level);
	}
}HeroMsg;

class Hero : public Sprite
{
public:
	//英雄选择动作核心逻辑
	void heroAction();
	//升lv级
	void upLevel(int lv) { _lv += lv; _hp *= _lv; _ap *= _lv; };
	//每回合减少的血量
	void getHurted() {
		_enemy_ap = 0;
		for (std::list<HeroMsg>::iterator iter = _l.begin(); iter != _l.end(); iter++)
		{
			if (iter->hero->getHp() > 0)
			{
				if (iter->hero->_mp >= iter->hero->_max_mp)
					_enemy_ap += iter->hero->_skill_ap;
				else
					_enemy_ap += iter->hero->_ap;
			}
		}
		_hp -= _enemy_ap;
	};
	//获取敌人信息
	void getEnemyInfor(std::list<HeroMsg>l) { _l = l; };
	//创建plist帧动画
	Animation* createPlistAnimation(std::string filename, std::string framename, int photonums);

	//初始化人物属性，以及坐标start_pos（默认坐标为屏幕中央）
	virtual void initPos(Vec2 start_pos) = 0;

	//前往敌人坐标并执行接下来的一系列动作
	virtual void heroRunToEnemyPos(Vec2& end_pos) = 0;
	//实现英雄攻击动画
	virtual void heroAttack() = 0;
	//实现英雄死亡动画
	virtual void heroDead() = 0;
	//移动到某一点并攻击
	virtual void heroSkill() = 0;

	// 获取英雄信息
	int getAp() { return _ap; };
	int getHp() { return _hp; };
	int getLv() { return _lv; };

	// 获取英雄阵营
	void changeMsg(int msg) { _msg = msg; };

	// 创建头顶血条
	void createHealthBar();
	// 更新头顶血条位置
	void updateHealthBarPosition();
	// 更新头顶血条显示
	//void updateHealthBarDisplay();
	void updateHealthBar(float dt);
	// 创建头顶蓝条
	void createMagicBar();
	// 更新头顶蓝条位置
	void updateMagicBarPosition();
	// 更新头顶蓝条显示
	void updateMagicBar(float dt);

protected:
	double _enemy_ap = 0;
	bool _reverse = false;//移动时是否翻转
	Vec2 _postion;//当前位置
	double _hp;
	double _ap;
	double _mp;
	int _lv;
	double _max_mp;
	double _max_hp;
	double _skill_ap;
	Sprite* _sprite;
	Animation* _run;
	Animation* _attack;
	Animation* _dead;
	Animation* _skill;
	std::list<HeroMsg>_l;

	ProgressTimer* _healthBar;  // 头顶血条
	ProgressTimer* _magicBar;  // 头顶蓝条

	int _msg;
};

class Samurai :public Hero
{
public:
	CREATE_FUNC(Samurai);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 320;
		_ap = 13;
		_mp = 0;
		_lv = 1;
		_max_mp = 4;
		_skill_ap = 1.5 * _ap;

		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};

class Knight :public Hero
{
public:
	CREATE_FUNC(Knight);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 350;
		_ap = 8;
		_mp = 0;
		_lv = 1;
		_max_mp = 5;
		_skill_ap = 1.5 * _ap;
		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};
class Berserker :public Hero
{
public:
	CREATE_FUNC(Berserker);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 200;
		_ap = 20;
		_mp = 0;
		_lv = 1;
		_max_mp = 3;
		_skill_ap = 2 * _ap;
		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};

class Kunoichi :public Hero
{
public:
	CREATE_FUNC(Kunoichi);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 290;
		_ap = 15;
		_mp = 0;
		_lv = 1;
		_max_mp = 4;
		_skill_ap = 1.5 * _ap;
		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};

class LightningMage :public Hero
{
public:
	CREATE_FUNC(LightningMage);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 280;
		_ap = 15;
		_mp = 0;
		_lv = 1;
		_max_mp = 5;
		_skill_ap = 1.7 * _ap;
		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};

class FireVizard :public Hero
{
public:
	CREATE_FUNC(FireVizard);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 300;
		_ap = 16;
		_mp = 0;
		_lv = 1;
		_max_mp = 6;
		_skill_ap = 2.5 * _ap;
		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};

class WandererMagican :public Hero
{
public:
	CREATE_FUNC(WandererMagican);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 280;
		_ap = 17;
		_mp = 0;
		_lv = 1;
		_max_mp = 5;
		_skill_ap = 2 * _ap;
		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};

class NinjaMonk :public Hero
{
public:
	CREATE_FUNC(NinjaMonk);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 300;
		_ap = 8;
		_mp = 0;
		_lv = 1;
		_max_mp = 2;
		_skill_ap = 1.1 * _ap;
		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};
class NinjaPeasant :public Hero
{
public:
	CREATE_FUNC(NinjaPeasant);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 300;
		_ap = 9;
		_mp = 0;
		_lv = 1;
		_max_mp = 3;
		_skill_ap = 1.2 * _ap;
		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};
class SamuraiCommander :public Hero
{
public:
	CREATE_FUNC(SamuraiCommander);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 320;
		_ap = 10;
		_mp = 0;
		_lv = 1;
		_max_mp = 4;
		_skill_ap = 1.5 * _ap;
		_max_hp = _hp;

		return true;
	}

	void initPos(Vec2 start_pos);

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill();
};

class BlueSlime : public Hero
{
public:
	CREATE_FUNC(BlueSlime);
	virtual bool init()
	{
		if (!Sprite::init()) return false;

		_hp = 100;
		_ap = 3;
		_mp = 0;
		_lv = 1;
		_max_mp = 6;
		_skill_ap = _ap;
		_max_hp = _hp;


		return true;
	};

	void initPos(Vec2 start_pos)
	{
		_postion = start_pos;
	};

	void heroAttack();
	void heroDead();
	void heroRunToEnemyPos(Vec2& end_pos);
	void heroSkill()
	{
		heroAttack();
	};
};