#include"GameHead.h"

bool HeroMoveController::init() {

	HeroSpeed = 30;
	
	registeMouseEvent();

	return true;

}

void HeroMoveController::registeMouseEvent() {

	auto myMouseListener = EventListenerMouse::create();

	//����ƶ�
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

	//���������볡����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);

}