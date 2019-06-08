#ifndef _ControllerListener_H_
#define _ControllerListener_H_

class ControllerListener :public cocos2d::Node{
public:
	//设置目标坐标
	virtual void setTagPosition(int x, int y) = 0;

	//获取目标坐标
	virtual cocos2d::Point getTagPosition() = 0;
};
#endif // !_ControllerListener_H_

