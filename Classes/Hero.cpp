#include"GameHead.h"
using namespace cocos2d;

bool Hero::init() {

	m_iHP = Ashe_iHP;
	m_iDefense = Ashe_iDenfense;
	m_isDead = false;
	m_iSpeed = PRI_SPEED;
	m_iLevel = 1;
	mNetworkId = 0;
	mPlayerId = 0;

	return true;
}

int Hero::getID() {
	return Ashe_ID;
}

void Hero::WriteForCRC(OutputMemoryBitStream& inStream)
{
    inStream.Write(mPlayerId);
    inStream.Write(mNetworkId);
}

void Hero::run() {
	SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("greenHero.plist", "greenHero.png");
	SpriteFrame*frame = NULL;
	Vector<SpriteFrame*> frameList;

	for (int i = 1; i < 7; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("greenHero%d.png", i));
		frameList.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.3f);
	Animate*animate = Animate::create(animation);

	m_sprite->runAction(animate);
	
}


/*void Hero::Q() {
	SpriteFrameCache*frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("greenHeroQ.plist", "greenHeroQ.png");
	SpriteFrame*frame = NULL;
	Vector<SpriteFrame*> frameList;

	for (int i = 1; i < 5; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("greenHeroQ%d.png", i));
		frameList.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.3f);
	Animate*animate = Animate::create(animation);

	m_sprite->runAction(animate);

}*/