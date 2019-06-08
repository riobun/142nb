#include"GameHead.h"
using namespace cocos2d;

bool MouseInput::init() {

	registeMouseEvent();

	return true;
}

void regieteMouseEvent() {

	auto myMouseListener = EventListenerMouse::create();

	//Êó±êÒÆ¶¯
	myMouseListener->onMouseMove = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

	};

	myMouseListener->onMouseDown = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

		auto target = eMouse->getCurrentTarget();
		if (target == map_Tag) {
			m_controllerListener->stopAllActions();
		}
	};

	myMouseListener->onMouseUp = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

		auto target = eMouse->getCurrentTarget();
		if (target == map_Tag) {
			auto target = static_cast<Sprite*>(event->getCurrentTarget());
			Vec2 cur_pos = m_controllerListener->getPosition();
			double iTime = (cur_pos - Vec2(eMouse->getCursorX(), eMouse->getCursorY())).length() / Pri_Speed;
			MoveTo* moveTo = MoveTo::create(iTime, Vec2(eMouse->getCursorX(), eMouse->getCursorY()));
			m_controllerListener->runAction(moveTo);

		}

	};

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, getChildByTag(mHero_Tag));
	eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener->clone(), getChildByTag(eHero_Tag));
}