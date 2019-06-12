#include "Equipment.h"
#include "ShopScene.h"
#include "GameHead.h"



Equipment::Equipment()
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


	_speedUpCallback = nullptr;
	_attackBuffCallback = nullptr;
	_defenseBuffCallback = nullptr;




	_deltaSum = 0;
}


Equipment::~Equipment()
{

}

Equipment* Equipment::create(const std::string normalImage, const std::string coolImage, const std::string buffType)
{
	Equipment* equipmentBtn = new Equipment();

	if (equipmentBtn && equipmentBtn->init(normalImage, coolImage, buffType)) {
		
		return equipmentBtn;
	}
	else {
		CC_SAFE_DELETE(equipmentBtn);
		return nullptr;
	}
}


bool Equipment::init()
{
	if (Node::init()) {
		return true;
	}
	return false;
}




bool Equipment::init(const std::string normalImage, const std::string coolImage, const std::string buffType)
{
	if (init())
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		
		auto buffButton = MenuItemImage::create(
			normalImage,
			coolImage,
			CC_CALLBACK_0(Equipment::menuHandler,this,buffType));

		if (buffButton == nullptr ||
			buffButton->getContentSize().width <= 0 ||
			buffButton->getContentSize().height <= 0)
		{
			log("'normalImage' and 'coolImage'");
		}
		else
		{
			buffButton->setScale(0.5f);
			buffButton->setAnchorPoint(Vec2(0, 0));


		}
		// create menu, it's an autorelease object
		auto buffMenu = Menu::create(buffButton, NULL);
		buffMenu->setPosition(Vec2::ZERO);
		
		this->addChild(buffMenu, 2);

		return true;
	}
	return false;
}





void Equipment::menuHandler(std::string buffType)
{
	
	if (buffType == "speedUpBuff")
		this->speedUpBuff();
	if (buffType == "attackBuff")
		this->attackBuff();
	if (buffType == "defenseBuff")
		this->attackBuff();

}


bool Equipment::speedUpBuff()
{
	log("speedUpBuff");
//	PRI_SPEED = PRI_SPEED+10;

	return true;
}
bool Equipment::attackBuff()
{
	log("attackBuff");
	return true;
} 
bool Equipment::defenseBuff()
{
	return true;
}

	

//============================
// !!!: public
//============================

void Equipment::setSkillEnable(const bool &enable)
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


const bool& Equipment::getSkillEnable() const
{
	return _skillEnable;
}


void Equipment::setupNormalImage(const std::string normalImage)
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
		setupAbnormalImage("");
	}

}

void Equipment::setupAbnormalImage(const std::string coolImage)
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



void Equipment::speedUpCallback(const Equipment::alSkillTouchCallback &callback)
{
	_speedUpCallback = callback;
}

void Equipment::attackBuffCallback(const Equipment::alSkillTouchCallback &callback)
{
	_attackBuffCallback = callback;
}

void Equipment::defenseBuffCallback(const Equipment::alSkillTouchCallback &callback)
{
	_defenseBuffCallback = callback;
}

