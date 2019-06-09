#include"GameHead.h"
using namespace cocos2d;

bool MouseInput::init() {

	registeMouseEvent();

	return true;
}

void MouseInput::registeMouseEvent() {

	auto myMouseListener = EventListenerMouse::create();

	//Êó±êÒÆ¶¯
	myMouseListener->onMouseMove = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

	};

	myMouseListener->onMouseDown = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

		auto target = eMouse->getCurrentTarget();
		

		m_controllerListener->stopAllActions();
		
	};

	myMouseListener->onMouseUp = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

		auto target = eMouse->getCurrentTarget();
			
			Vec2 cur_pos = m_controllerListener->getPosition();
			double iTime = (cur_pos - Vec2(eMouse->getCursorX(), eMouse->getCursorY())).length() / PRI_SPEED;
			MoveTo* moveTo = MoveTo::create(iTime, Vec2(eMouse->getCursorX(), eMouse->getCursorY()));
			m_controllerListener->runAction(moveTo);

		

	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this->getChildByTag(mHero_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener->clone(), this->getChildByTag(eHero_Tag));
}