#include"GameHead.h"
using namespace cocos2d;

bool HeroMoveController::init() {

	
	
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

		m_controllerListener->stopAllActions();
		EventMouse* eMouse = (EventMouse*)event;
		//Vec2 cur_pos = m_controllerListener->getPosition();
		//int isClick_ID = 0;
		

	};

	myMouseListener->onMouseUp = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;
		Vec2 cur_pos = m_controllerListener->getPosition();
		extern vector<Entity*> eETT_ptr;
		if (eETT_ptr.size()) {
			for (auto i = 0; i < eETT_ptr.size(); i++) {

				if (eETT_ptr[i] != NULL) {
					float distance = (eETT_ptr[i]->getPosition() - cur_pos).length();
					float isClick = 30;
					if ((Vec2(eMouse->getCursorX(), eMouse->getCursorY()) - eETT_ptr[i]->getPosition()).length() <= isClick) {

						if (distance <= attackScale) {
							eETT_ptr[i]->hurtMe(i, Ashe_attackValue, eETT_ptr);
							break;
						}
					}
				}

				if (i == eETT_ptr.size() - 1) {
					double iTime = (cur_pos - Vec2(eMouse->getCursorX(), eMouse->getCursorY())).length() / PRI_SPEED;
					MoveTo* moveTo = MoveTo::create(iTime, Vec2(eMouse->getCursorX(), eMouse->getCursorY()));
					m_controllerListener->runAction(moveTo);
					

				}
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener, this);
	
}


