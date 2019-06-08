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
	  �����Ƿ�����ȴ��
	 */
	virtual const bool& isSkillCD() const { return _isSkillCD; }

	/**
	 *  ��������״̬�µ�Image
	 */
	virtual void setupNormalImage(const std::string normalImage);
	/**
	 *  ������ȴ״̬�µ�Image
	 */
	virtual void setupCoolImage(const std::string coolImage);

	/**
	 ���ܰ��µĻص�
	 */
	virtual void addQPressedCallback(const alSkillTouchCallback& callback);
	virtual void addWPressedCallback(const alSkillTouchCallback& callback);
	virtual void addEPressedCallback(const alSkillTouchCallback& callback);
	virtual void addTabPressedCallback(const alSkillTouchCallback& callback);
	virtual void addPPressedCallback(const alSkillTouchCallback& callback);

	/**
	 ��Ӽ���CD������Ļص�
	 */
	virtual void addSkillCDEndCallback(const alSkillCDEndCallback& callback);


protected:
	virtual bool init() override;
	virtual bool init(const std::string normalImage, const std::string coolImage, float skillTime);
	
	/**
	 ��Ӽ����¼�
	 */
	virtual void addKeyListener();

	/**
	ִ��keyCode���²���
	*/
	virtual bool keyQPressed();
	virtual bool keyWPressed();
	virtual bool keyEPressed();
	virtual bool keyTabPressed();
	virtual bool keyPPressed();
    
	virtual bool isKeyPressed(EventKeyboard::KeyCode keyCode);
	virtual void keyPressedDuration(EventKeyboard::KeyCode code);
	
	/**
	  ��ʼ������ȴ
	 */
	virtual void startSkillCDAction();

	/**
	 ���ü�����ȴ
	 */
	virtual void resetSkillCDAction();

	/**
	 ������ȴʱ��
	 */
	virtual void reduceSkillCDTimeAction(float time);

protected:
	Sprite* _pSkill;
	ProgressTimer* _pProgressCD;


	//** �����Ƿ���� *//
	CC_PROPERTY_PASS_BY_REF(bool, _skillEnable, SkillEnable);
	//** �����Ƿ�����ȴʱ�� *//
	bool _isSkillCD = false;
	//** ������ȴʱ�� *//
	CC_SYNTHESIZE_PASS_BY_REF(float, _skillCoolTime, SkillCoolTime);
	//** ��ѹʱ�� *//
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
	//** �Ƿ��ܴ������� *//
	bool _isSkillTouchEnd = true;
	//** ����ʱ������������Ҫ���� *//
	float _deltaSum = 0;
	
};

#endif /* SkillButton_h */
