#include"GameHead.h"
using namespace cocos2d;

bool HeroMoveController::init() {

	
	
	registeMouseEvent();

	return true;

}

void HeroMoveController::registeMouseEvent() {

	auto myMouseListener = EventListenerMouse::create();

	//Êó±êÒÆ¶¯
	myMouseListener->onMouseMove = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

	};

	myMouseListener->onMouseDown = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

		m_controllerListener->stopAllActions();

	};

	myMouseListener->onMouseUp = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;
		Vec2 cur_pos = m_controllerListener->getPosition();
		double iTime = (cur_pos - Vec2(eMouse->getCursorX(), eMouse->getCursorY())).length() /PRI_SPEED;
		MoveTo* moveTo = MoveTo::create(iTime, Vec2(eMouse->getCursorX(), eMouse->getCursorY()));
		m_controllerListener->runAction(moveTo);

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener->clone(), getChildByTag(eHero_Tag));
}