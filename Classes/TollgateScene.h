

#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include"GameHead.h"

using namespace cocos2d;

class TollgateScene :public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(TollgateScene);
	
	//坐标转换，opgl坐标转换为Tiled地图坐标（每块小地图的坐标）
	cocos2d::Vec2 toTileCoord(cocos2d::Vec2 position);
	cocos2d::Vec2 toScreenCoord(cocos2d::Vec2 position);

	void addHero(Sprite* map);
private:
	cocos2d::Size visibleSize;
	cocos2d::Sprite *sprite;
	cocos2d::TMXTiledMap *map;
	cocos2d::LabelTTF *label;



};


#endif
