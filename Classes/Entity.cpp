#include"GameHead.h"

using namespace cocos2d;

Entity::Entity() :
	m_sprite(NULL),
		m_sName(" "),
		m_iHP(1),
		m_iDefense(1),
		m_isDead(false),
		m_iSpeed(PRI_SPEED),
		m_iLevel(1),
		mNetworkId(0),
		mPlayerId(0)
{
}

Entity::~Entity() {

}

void Entity::bindSprite(Sprite* sprite) {
	if (this->m_sprite != NULL) {
		m_sprite->removeFromParentAndCleanup(true);
	}

	this->m_sprite = sprite;
	this->addChild(m_sprite);

	Size size = m_sprite->getContentSize();
	this->setContentSize(size);

	onBindSprite();
}

Sprite* Entity::getSprite() {
	return this->m_sprite;
}

void Entity::hurtMe(int iHurtValue) {
	if (m_isDead) {
		return;
	}

	//最小伤害值为1
	if (iHurtValue <= getiDefense()) {
		iHurtValue = 1;
	}

	int iCurHP = getiHP();
	int iAfterHP = iCurHP - iHurtValue;
		setiHP(iAfterHP);



	if (iAfterHP > 0) {
	}
	else {
		m_isDead = true;
		//死亡
		onDead();

	}
}

bool Entity::isDead() {
	return this->m_isDead;
}

void Entity::onDead() {
	this->removeFromParent();
	NetworkManager::sInstance->UnregisterGameObject(this);
}

void Entity::onBindSprite() {

}


void Entity::onHurt() {

}


Point Entity::getTagPosition() {
	return getPosition();
}
void Entity::setTagPosition(int x, int y) {
	setPosition(Point(x, y));


}

void Entity::setController(Controller1* controller) {
	this->m_controller = controller;
	m_controller->setControllerListener(this);
}

void Entity::SetNetworkId(uint32_t inNetworkId)
{
    //this doesn't put you in the map or remove you from it
    mNetworkId = inNetworkId;
}