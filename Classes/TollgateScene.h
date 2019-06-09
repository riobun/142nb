

#ifndef _TollgateScene_H_
#define _TollgateScene_H_


#include "GameHead.h"
USING_NS_CC;



class TollgateScene :public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void update(float dt);
	
	// a selector callback
	void EnterShop(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(TollgateScene);
	
	//����ת����opgl����ת��ΪTiled��ͼ���꣨ÿ��С��ͼ�����꣩
	cocos2d::Vec2 toTileCoord(cocos2d::Vec2 position);
	cocos2d::Vec2 toScreenCoord(cocos2d::Vec2 position);

	void addHero(Sprite* map);
private:
	cocos2d::Size visibleSize;
	cocos2d::Sprite *sprite;
	cocos2d::TMXTiledMap *map;
	cocos2d::LabelTTF *label;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;



};




#endif
