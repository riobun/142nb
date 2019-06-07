

#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include"GameHead.h"

using namespace cocos2d;

class TollgateScene :public Layer {
public:
	static Scene* createScene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
	void addHero(Sprite* map);

};


#endif
