#ifndef _Controller1_H_
#define _Controller1_H_

#include"GameHead.h"

using namespace cocos2d;

class Controller1 :public Node {
public:
	//���ü�������
	void setControllerListener(ControllerListener* controllerListener);
protected:
	ControllerListener* m_controllerListener;
};
#endif // !_Controller_H_

