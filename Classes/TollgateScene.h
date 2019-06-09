

#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include"GameHead.h"

using namespace cocos2d;

class TollgateScene :public cocos2d::Layer {
public:
    TollgateScene();
    ~TollgateScene();
	virtual bool init();
    static cocos2d::Scene* createScene();
    static unique_ptr< TollgateScene >	sInstance;
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void update(float dt);
    void searchFinish();//在网络搜索完毕后调用
	// implement the "static create()" method manually
	CREATE_FUNC(TollgateScene);
	
	//����ת����opgl����ת��ΪTiled��ͼ���꣨ÿ��С��ͼ�����꣩
	cocos2d::Vec2 toTileCoord(cocos2d::Vec2 position);
	cocos2d::Vec2 toScreenCoord(cocos2d::Vec2 position);

	void addHero(Sprite* map, uint32_t side);
    static TollgateScene* slayer;
private:
	cocos2d::Size visibleSize;
	cocos2d::Sprite *sprite;
	cocos2d::TMXTiledMap *map;
	cocos2d::LabelTTF *label;

    cocos2d::Sprite* m_map;

};

#endif
