#ifndef _ControllerListener_H_
#define _ControllerListener_H_

#include"GameHead.h"
using namespace cocos2d;

class ControllerListener :public Node{
public:
	//����Ŀ������
	virtual void setTagPosition(int x, int y) = 0;

	//��ȡĿ������
	virtual Point getTagPosition() = 0;
};
#endif // !_ControllerListener_H_

