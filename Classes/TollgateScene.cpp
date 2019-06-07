#include"GameHead.h"

Scene* TollgateScene::createScene() {
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);

	
	return scene;
}

void TollgateScene::addHero(Sprite* map) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建精灵
	Sprite* heroSprite = Sprite::create("Ashe1.png");
	heroSprite->setScale(SPRITE_SIZE);

	 //把精灵绑定到英雄对象上
	Hero* mHero = Hero::create();
	mHero->bindSprite(heroSprite);

	//设置英雄出生点
	mHero->setAnchorPoint(Vec2(0, 0));
	mHero->setPosition(100, visibleSize.height/2 +50);

	this->addChild(mHero);

	//创建英雄移动控制器
	HeroMoveController* heroMoveController = HeroMoveController::create();

	//把控制器添加到场景中
	this->addChild(heroMoveController);

	//设置控制器到英雄身上
	mHero->setController(heroMoveController);
}

bool TollgateScene::init() {
	if (!Layer::init())
	{
		return false;

	}

	//添加地图
	auto map = Sprite::create("Map.png");
	map->setScale(1.586f);
	map->setPosition(Point(0, 0));
	map->setAnchorPoint(Vec2(0, 0));
	this->addChild(map,-1);//默认添加的位置是左下角

	addHero(map);
	
	return true;
}