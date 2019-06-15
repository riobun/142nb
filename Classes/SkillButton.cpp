#include "SkillButton.h"
#include "GameHead.h"


#define SCHEDULE_SKILL_UPDATE_TIME "SCHEDULE_SKILL_UPDATE_TIME"
#define SKILL_UPDATE_INTERVAL 0.1



SkillButton::SkillButton()
{
	_pSkill = nullptr;
	_pProgressCD = nullptr;


	_skillEnable = true;
	_skillCoolTime = 0;
	_isSkillCD = false;
	_pressTime = 0;
	_tUpdateInerval = 0;

	_normalImageName = "";
	_coolImageName = "";
    

	_QPressedCallback = nullptr;
	_WPressedCallback = nullptr;
	_EPressedCallback = nullptr;
	_TabPressedCallback = nullptr;
	_PPressedCallback = nullptr;
	_skillCDEndCallback = nullptr;


	_deltaSum = 0;
}


SkillButton::~SkillButton()
{

}

SkillButton* SkillButton::create(const std::string normalImage, const std::string coolImage, float skillTime)
{
	SkillButton* skillBtn = new SkillButton();
	if (skillBtn && skillBtn->init(normalImage, coolImage, skillTime)) {
		return skillBtn;
	}
	else {
		CC_SAFE_DELETE(skillBtn);
		return nullptr;
	}
}


bool SkillButton::init()
{
	if (Node::init()) {
		return true;
	}
	return false;
}

bool SkillButton::init(const std::string normalImage, const std::string coolImage, float skillTime)
{
	if (init()) 
	{
		_skillCoolTime = skillTime;
		setupNormalImage(normalImage);
		setupCoolImage(coolImage);
		 
		addKeyListener();
		return true;
	}
	return false;
}





void SkillButton::addKeyListener()
{
	
	auto listener = EventListenerKeyboard::create();
		
	// Implementation of the keyboard event callback function prototype
	listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) 
	{
		keys[keyCode] = true;
		this->isKeyPressed(keyCode);
	};

	listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
	{
		keys[keyCode] = false;
		this->isKeyPressed(keyCode);
	};
	
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

}


bool SkillButton::isKeyPressed(EventKeyboard::KeyCode keyCode)//判断是否按下某按键
{
	if (keys[keyCode]) 
	{
		this->keyPressedDuration(keyCode);
		return true;
	}
	else 
	{
		return false;
	}
}

void SkillButton::keyPressedDuration(EventKeyboard::KeyCode code) 
{

	switch (code) {
	case EventKeyboard::KeyCode::KEY_Q:
		this->keyQPressed();
		break;
	case EventKeyboard::KeyCode::KEY_W:
		this->keyWPressed();
		break;
	case EventKeyboard::KeyCode::KEY_E:
		this->keyEPressed();
		break;
	case EventKeyboard::KeyCode::KEY_TAB:
		this->keyTabPressed();
		break;
	case EventKeyboard::KeyCode::KEY_P:
		this->keyPPressed();
		break;
	default:
		break;

	}

}

bool SkillButton::keyQPressed()
{
	if (_skillEnable && !_isSkillCD)
	{
		
	

		// 开始回调
		if (_QPressedCallback)
		{
			_QPressedCallback(0);


			_isSkillTouchEnd = false;
			return true;
		}
	}

	// 开始读冷却
	this->startSkillCDAction();

	_isSkillTouchEnd = true;
	return false;

}

bool SkillButton::keyWPressed()
{
	if (_skillEnable && !_isSkillCD)
	{
		// 开始回调
		if (_WPressedCallback)
		{
			_WPressedCallback(0);


			_isSkillTouchEnd = false;
			return true;
		}
	}

	// 开始读冷却
	this->startSkillCDAction();
	_isSkillTouchEnd = true;
	return false;
}
bool SkillButton::keyEPressed()
{
	if (_skillEnable && !_isSkillCD)
	{
		// 开始回调
		if (_EPressedCallback)
		{
			_EPressedCallback(0);


			_isSkillTouchEnd = false;
			return true;
		}
	}

	// 开始读冷却
	this->startSkillCDAction();
	_isSkillTouchEnd = true;
	return false;
}
bool SkillButton::keyTabPressed()
{
	if (_skillEnable && !_isSkillCD)
	{
		// 开始回调
		if (_TabPressedCallback)
		{
			_TabPressedCallback(0);


			_isSkillTouchEnd = false;
			return true;
		}
	}

	// 开始读冷却
	this->startSkillCDAction();
	_isSkillTouchEnd = true;
	return false;
}
bool SkillButton::keyPPressed()
{
	if (_skillEnable && !_isSkillCD)
	{
		// 开始回调
		if (_PPressedCallback)
		{
			_PPressedCallback(0);


			_isSkillTouchEnd = false;
			return true;
		}
	}

	// 开始读冷却
	this->startSkillCDAction();


	_isSkillTouchEnd = true;
	return false;
}

void SkillButton::startSkillCDAction()
{
	if (_skillCoolTime > 0) 
	{
		_isSkillCD = true;
		_pProgressCD->setPercentage(100);
		_pProgressCD->stopAllActions();
		_pProgressCD->runAction(Sequence::create(ProgressTo::create(_skillCoolTime, 0), CallFunc::create([this] 
		{
			// 技能冷却结束
			_isSkillCD = false;
			// 技能冷却完成后的回调
			if (_skillCDEndCallback)
			{
				_skillCDEndCallback();
			}
		}), NULL));
	}
	else 
	{
		_pProgressCD->stopAllActions();
		_pProgressCD->setPercentage(0);
		_isSkillCD = false;
		// 技能冷却完成后的回调
		if (_skillCDEndCallback) 
		{
			_skillCDEndCallback();
		}
	}


}

void SkillButton::resetSkillCDAction()
{
	if (_isSkillCD) {
		_pProgressCD->stopAllActions();
		_pProgressCD->setPercentage(0);
		_isSkillCD = false;
		// 技能冷却完成后的回调
		if (_skillCDEndCallback) {
			_skillCDEndCallback();
		}
	}
}

void SkillButton::reduceSkillCDTimeAction(float time)
{
	if (_isSkillCD) {
		_pProgressCD->stopAllActions();
		float percent = _pProgressCD->getPercentage();
		float remainingTime = MIN(0, percent*_skillCoolTime - time);
		if (remainingTime > 0) {
			float nowPercent = 100.f / _skillCoolTime * remainingTime;
			_pProgressCD->setPercentage(nowPercent);
			_pProgressCD->runAction(Sequence::create(ProgressTo::create(remainingTime, 0), CallFunc::create([this] {
				// 技能冷却结束
				_isSkillCD = false;
				// 技能冷却完成后的回调
				if (_skillCDEndCallback) {
					_skillCDEndCallback();
				}
			}), NULL));
		}
		else {
			resetSkillCDAction();
		}
	}
}




//============================
// !!!: public
//============================

void SkillButton::setSkillEnable(const bool &enable)
{
	if (_skillEnable != enable) {
		_skillEnable = enable;
		if (!_skillEnable) {
			_pProgressCD->stopAllActions();
			_pProgressCD->setPercentage(100);
			_isSkillCD = true;
		}
	}
}


const bool& SkillButton::getSkillEnable() const
{
	return _skillEnable;
}


void SkillButton::setupNormalImage(const std::string normalImage)
{
	_normalImageName = normalImage;
	CCASSERT(!normalImage.empty(), "SkillButton : normalImage is empty");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(normalImage);
	if (_pSkill) {
		(frame ? _pSkill->setSpriteFrame(frame) : _pSkill->setSpriteFrame(normalImage));
	}
	else {
		_pSkill = frame ? Sprite::createWithSpriteFrame(frame) : Sprite::create(normalImage);
		this->addChild(_pSkill, 0);
	}
	setContentSize(_pSkill->getContentSize());

	if (_coolImageName.empty()) {
		setupCoolImage("");
	}

}

void SkillButton::setupCoolImage(const std::string coolImage)
{
	_coolImageName = coolImage;
	Sprite* coolSprite = nullptr;
	if (coolImage.empty()) {
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_normalImageName);
		coolSprite = frame ? Sprite::createWithSpriteFrame(frame) : Sprite::create(_normalImageName);
		coolSprite->setColor(Color3B(64, 64, 64));
	}
	else {
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(coolImage);
		coolSprite = frame ? Sprite::createWithSpriteFrame(frame) : Sprite::create(coolImage);
	}
	if (_pProgressCD) {
		_pProgressCD->setSprite(coolSprite);
	}
	else {
		_pProgressCD = ProgressTimer::create(coolSprite);
		_pProgressCD->setType(ProgressTimer::Type::RADIAL);
		_pProgressCD->setReverseProgress(true);
		_pProgressCD->setPercentage(0);
		this->addChild(_pProgressCD, 1);
	}
}



void SkillButton::addQPressedCallback(const SkillButton::alSkillTouchCallback &callback)
{
	extern Hero* m_hero;

	Animation *skillQ = Animation::create();
	for (int i = 1; i < 7; i++)
	{
		__String *frameName = __String::createWithFormat("greenHero%d.png", i);
		log("frameName=%s", frameName->getCString());
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->
			getSpriteFrameByName(frameName->getCString());
		skillQ->addSpriteFrame(spriteFrame);
	}

	skillQ->setDelayPerUnit(0.15f);
	skillQ->setRestoreOriginalFrame(true);
	Animate*action = Animate::create(skillQ);
   
	m_hero->runAction(action);


	_QPressedCallback = callback;
}

void SkillButton::addWPressedCallback(const SkillButton::alSkillTouchCallback &callback)
{
	_WPressedCallback = callback;
}

void SkillButton::addEPressedCallback(const SkillButton::alSkillTouchCallback &callback)
{
	// 开始读冷却
	this->startSkillCDAction();
	_EPressedCallback = callback;
}

void SkillButton::addTabPressedCallback(const SkillButton::alSkillTouchCallback &callback)
{
	_TabPressedCallback = callback;
}

void SkillButton::addPPressedCallback(const SkillButton::alSkillTouchCallback &callback)
{
	_PPressedCallback = callback;
}

void SkillButton::addSkillCDEndCallback(const alSkillCDEndCallback& callback)
{
	_skillCDEndCallback = callback;
}
