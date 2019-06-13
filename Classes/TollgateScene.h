

#ifndef _TollgateScene_H_
#define _TollgateScene_H_
#define TAG_DATA_LAYER 2

#include"GameHead.h"

using namespace cocos2d;



class TollgateScene :public cocos2d::Layer {
public:
	friend class HeroMoveController;
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(TollgateScene);
	
	//����ת����opgl����ת��ΪTiled��ͼ���꣨ÿ��С��ͼ�����꣩
	cocos2d::Vec2 toTileCoord(cocos2d::Vec2 position);
	cocos2d::Vec2 toScreenCoord(cocos2d::Vec2 position);


	Hero* m_hero;
	void addHero(Sprite* map);
	void addTower(Sprite* map);
	void TollgateScene::shop(Ref* pSender);

	void addHero(Sprite* map, uint32_t side);
	void addNumberNode();
	void logic(float dt);
    static TollgateScene* slayer;

private:
	cocos2d::Size visibleSize;
	cocos2d::Sprite *sprite;
	cocos2d::TMXTiledMap *map;
	cocos2d::LabelTTF *label;
	
	LaneTower* m_laneTower;
	Crystal* m_crystal;
	LaneTower* e_laneTower;
	Crystal* e_crystal;

};


#endif
