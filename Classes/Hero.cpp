#include"GameHead.h"
using namespace cocos2d;
extern double Ashe_iDenfense;
extern double PRI_SPEED;


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

void Hero::onDead(int i) {
	extern vector<Entity*> eETT_ptr;
	eETT_ptr.erase(eETT_ptr.begin() + i);
	this->removeFromParent();
}

void Hero::mHero_onDead(int i) {
	extern vector<Entity*> mETT_ptr;
	mETT_ptr.erase(mETT_ptr.begin() + i);
	this->removeFromParent();
}
