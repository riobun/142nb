#ifndef _Controller1_H_
#define _Controller1_H_

class Controller1 :public cocos2d::Node {
public:
	//���ü�������
	void setControllerListener(ControllerListener* controllerListener);
protected:
	ControllerListener* m_controllerListener;
};
#endif // !_Controller_H_

