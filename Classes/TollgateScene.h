

#ifndef _TollgateScene_H_
#define _TollgateScene_H_

class TollgateScene :public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
	void addHero(cocos2d::Sprite* map);

};


#endif
