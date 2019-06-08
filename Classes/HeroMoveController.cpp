#include"GameHead.h"

bool HeroMoveController::init() {

	HeroSpeed = 30;
	
	registeMouseEvent();

	return true;

}

void HeroMoveController::registeMouseEvent() {

	auto myMouseListener = EventListenerMouse::create();

	//鼠标移动
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
		double iTime = (cur_pos - Vec2(eMouse->getCursorX(), eMouse->getCursorY())).length() / HeroSpeed;
		MoveTo* moveTo = MoveTo::create(iTime, Vec2(eMouse->getCursorX(), eMouse->getCursorY()));
		m_controllerListener->runAction(moveTo);
		

	};

	//将监听器与场景绑定
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);

}