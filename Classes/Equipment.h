#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include "cocos2d.h"

USING_NS_CC;

class Equipment :public cocos2d::CCNode
{
public:
	typedef std::function<void(float pressTime)> alSkillTouchCallback;



public:
	
	static Equipment* create(const std::string normalImage, const std::string coolImage, const std::string buffChoose);

	Equipment();
	virtual ~Equipment();

	/**
	  技能是否可以购买
	 */
	virtual const bool& isCanBuy() const { return _isSkillCD; }

	/**
	 *  设置可选状态下的Image
	 */
	virtual void setupNormalImage(const std::string normalImage);
	/**
	 *  设置不可选状态下的Image
	 */
	virtual void setupAbnormalImage(const std::string coolImage);
	/**
     *   执行keyCode按下操作
     */
	virtual bool speedUpBuff();
	virtual bool attackBuff();
	virtual bool defenseBuff();



	/**
	 购买装备的回调
	 */
	virtual void speedUpCallback(const alSkillTouchCallback& callback);
	virtual void attackBuffCallback(const alSkillTouchCallback& callback);
	virtual void defenseBuffCallback(const alSkillTouchCallback& callback);

	void Equipment::menuHandler(const std::string buffType);





protected:
	virtual bool init() override;
	virtual bool init(const std::string normalImage, const std::string coolImage, const std::string buffType);



protected:
	Sprite* _pSkill;
	ProgressTimer* _pProgressCD;


	//** 技能是否可用 *//
	CC_PROPERTY_PASS_BY_REF(bool, _skillEnable, SkillEnable);
	//** 技能是否处于冷却时间 *//
	bool _isSkillCD = false;
	//** 技能冷却时间 *//
	CC_SYNTHESIZE_PASS_BY_REF(float, _skillCoolTime, SkillCoolTime);
	//** 按压时间 *//
	CC_SYNTHESIZE_READONLY_PASS_BY_REF(float, _pressTime, PressTime);
	//**  *//
	float _tUpdateInerval = 0;


	std::string _normalImageName;
	std::string _coolImageName;

	alSkillTouchCallback _speedUpCallback;
	alSkillTouchCallback _attackBuffCallback;
	alSkillTouchCallback _defenseBuffCallback;




private:
	//** 是否技能触摸结束 *//
	bool _isSkillTouchEnd = true;
	//** 更新时间增量数，主要用于 *//
	float _deltaSum = 0;

};

#endif /* SkillButton_h */
