#ifndef __BASEMAP_CLASS_H__
#define __BASEMAP_CLASS_H__

#include "cocos2d.h"

class BaseMap :public cocos2d::Layer
{
public:
	CREATE_FUNC(BaseMap);
	//��ǰ�ؿ�
	CC_SYNTHESIZE(int, level, level);
	//�󶨰�����

};

#endif //__MAP_CLASS_H__
