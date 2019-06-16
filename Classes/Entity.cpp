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

void Entity::hurtMe(int i,int iHurtValue, vector<Entity*> iETT_ptr) {
	if (m_isDead) {
		return;
	}

	//��С�˺�ֵΪ1
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
		//����
		onDead(i, iETT_ptr);

	}
}

void Entity::hurtMeHero(int i, int iHurtValue, vector<Entity*> iETT_ptr) {
	if (m_isDead) {
		return;
	}

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
		//����
		mHero_onDead(i, iETT_ptr);

	}
}

bool Entity::isDead() {
	return this->m_isDead;
}

void Entity::onDead(int i, vector<Entity*> iETT_ptr) {
	
	

	//NetworkManager::sInstance->UnregisterGameObject(this);
}

void Entity::mHero_onDead(int i, vector<Entity*> iETT_ptr) {


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