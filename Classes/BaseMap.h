#ifndef __BASEMAP_CLASS_H__
#define __BASEMAP_CLASS_H__

#include "cocos2d.h"

class BaseMap :public cocos2d::Layer
{
public:
	CREATE_FUNC(BaseMap);
	//当前关卡
	CC_SYNTHESIZE(int, level, level);
	//绑定按键层

};

#endif //__MAP_CLASS_H__
