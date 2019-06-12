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
	  �����Ƿ���Թ���
	 */
	virtual const bool& isCanBuy() const { return _isSkillCD; }

	/**
	 *  ���ÿ�ѡ״̬�µ�Image
	 */
	virtual void setupNormalImage(const std::string normalImage);
	/**
	 *  ���ò���ѡ״̬�µ�Image
	 */
	virtual void setupAbnormalImage(const std::string coolImage);
	/**
     *   ִ��keyCode���²���
     */
	virtual bool speedUpBuff();
	virtual bool attackBuff();
	virtual bool defenseBuff();



	/**
	 ����װ���Ļص�
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

	alSkillTouchCallback _speedUpCallback;
	alSkillTouchCallback _attackBuffCallback;
	alSkillTouchCallback _defenseBuffCallback;




private:
	//** �Ƿ��ܴ������� *//
	bool _isSkillTouchEnd = true;
	//** ����ʱ������������Ҫ���� *//
	float _deltaSum = 0;

};

#endif /* SkillButton_h */
