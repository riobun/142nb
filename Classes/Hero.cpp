#include"GameHead.h"
using namespace cocos2d;

bool Hero::init() {
	return true;
}

void Hero::run(Sprite* sprite) {
	
	double iSpeed = PRI_SPEED;
	//Sprite* mouse = Sprite::create("mouse.png");
	//�����¼�����������������¼�
	auto myMouseListener = EventListenerMouse::create();
	//����ƶ�
	myMouseListener->onMouseMove = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;
		//mouse->setPosition(eMouse->getCursorX(), eMouse->getCursorY());

	};
	//��갴��
	myMouseListener->onMouseDown = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

		sprite->stopAllActions();

	};
	//��굯��
	myMouseListener->onMouseUp = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;
		Vec2 cur_pos = sprite->getPosition();
		double iTime = (cur_pos - Vec2(eMouse->getCursorX(), eMouse->getCursorY())).length() / iSpeed;
		MoveTo* moveTo = MoveTo::create(iTime, Vec2(eMouse->getCursorX(), eMouse->getCursorY()));
		sprite->runAction(moveTo);

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener,this);

}

void Hero::WriteForCRC(OutputMemoryBitStream& inStream)
{
    inStream.Write(mPlayerId);
    inStream.Write(mNetworkId);
}
