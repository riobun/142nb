#ifndef _ControllerListener_H_
#define _ControllerListener_H_

class ControllerListener :public cocos2d::Node{
public:
	//����Ŀ������
	virtual void setTagPosition(int x, int y) = 0;

	//��ȡĿ������
	virtual cocos2d::Point getTagPosition() = 0;
};
#endif // !_ControllerListener_H_

