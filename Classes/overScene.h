#ifndef __OVER_SCENE_H__
#define __OVER_SCENE_H__

#include "cocos2d.h"

class overScene : public cocos2d::Scene
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);

	// a selector callback

	// implement the "static create()" method manually
	CREATE_FUNC(overScene);
};

#endif // __HELLOWORLD_SCENE_H__


