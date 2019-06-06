#include"GameHead.h"

bool Hero::init() {
	return true;
}

void Hero::run(Sprite* sprite) {
	
	double iSpeed = PRI_SPEED;
	//Sprite* mouse = Sprite::create("mouse.png");
	//创建事件监听器，监听鼠标事件
	auto myMouseListener = EventListenerMouse::create();
	//鼠标移动
	myMouseListener->onMouseMove = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;
		//mouse->setPosition(eMouse->getCursorX(), eMouse->getCursorY());

	};
	//鼠标按下
	myMouseListener->onMouseDown = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;

		sprite->stopAllActions();

	};
	//鼠标弹起
	myMouseListener->onMouseUp = [=](Event * event) {

		EventMouse* eMouse = (EventMouse*)event;
		Vec2 cur_pos = sprite->getPosition();
		double iTime = (cur_pos - Vec2(eMouse->getCursorX(), eMouse->getCursorY())).length() / iSpeed;
		MoveTo* moveTo = MoveTo::create(iTime, Vec2(eMouse->getCursorX(), eMouse->getCursorY()));
		sprite->runAction(moveTo);

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myMouseListener,this);

}

