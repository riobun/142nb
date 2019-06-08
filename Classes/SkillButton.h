#ifndef __SKILL_BUTTON_H__
#define __SKILL_BUTTON_H__

#include "cocos2d.h"

USING_NS_CC;

class SkillButton :public cocos2d:: CCNode
{
public:
	typedef std::function<void(float pressTime)> alSkillClickCallback;
	typedef std::function<void(float pressTime)> alSkillTouchCallback;
	typedef std::function<void(void)> alSkillCDEndCallback;



public:
	static SkillButton* create(const std::string normalImage, const std::string coolImage , float skillTime );

	SkillButton();
	virtual ~SkillButton();

	/**
	  技能是否处于冷却中
	 */
	virtual const bool& isSkillCD() const { return _isSkillCD; }

	/**
	 *  设置正常状态下的Image
	 */
	virtual void setupNormalImage(const std::string normalImage);
	/**
	 *  设置冷却状态下的Image
	 */
	virtual void setupCoolImage(const std::string coolImage);

	/**
	 技能按下的回调
	 */
	virtual void addQPressedCallback(const alSkillTouchCallback& callback);
	virtual void addWPressedCallback(const alSkillTouchCallback& callback);
	virtual void addEPressedCallback(const alSkillTouchCallback& callback);
	virtual void addTabPressedCallback(const alSkillTouchCallback& callback);
	virtual void addPPressedCallback(const alSkillTouchCallback& callback);

	/**
	 添加技能CD结束后的回调
	 */
	virtual void addSkillCDEndCallback(const alSkillCDEndCallback& callback);


protected:
	virtual bool init() override;
	virtual bool init(const std::string normalImage, const std::string coolImage, float skillTime);
	
	/**
	 添加键盘事件
	 */
	virtual void addKeyListener();

	/**
	执行keyCode按下操作
	*/
	virtual bool keyQPressed();
	virtual bool keyWPressed();
	virtual bool keyEPressed();
	virtual bool keyTabPressed();
	virtual bool keyPPressed();
    
	virtual bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	virtual void keyPressedDuration(EventKeyboard::KeyCode code);
	
	/**
	  开始技能冷却
	 */
	virtual void startSkillCDAction();

	/**
	 重置技能冷却
	 */
	virtual void resetSkillCDAction();

	/**
	 减少冷却时间
	 */
	virtual void reduceSkillCDTimeAction(float time);

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

	alSkillCDEndCallback _skillCDEndCallback;
	
	alSkillTouchCallback _QPressedCallback;
	alSkillTouchCallback _WPressedCallback;
	alSkillTouchCallback _EPressedCallback;
	alSkillTouchCallback _TabPressedCallback;
	alSkillTouchCallback _PPressedCallback;


	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;


private:
	//** 是否技能触摸结束 *//
	bool _isSkillTouchEnd = true;
	//** 更新时间增量数，主要用于 *//
	float _deltaSum = 0;
	
};

#endif /* SkillButton_h */
