#include"GameHead.h"

using namespace cocos2d;

Scene* TollgateScene::createScene() {
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}

void TollgateScene::addHero(Sprite* map) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//创建精灵
	Sprite* heroSprite = Sprite::create("Ashe1.png");
	heroSprite->setScale(SPRITE_SIZE);

	 //把精灵绑定到英雄对象上
	Hero* mHero = Hero::create();
	mHero->bindSprite(heroSprite);
	mHero->run(heroSprite);

	//设置英雄出生点
	mHero->setPosition(Point(50, visibleSize.height / 2));

	map->addChild(mHero);

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
	auto map = Sprite::create("map.png");
	this->addChild(map);//默认添加的位置是左下角

	addHero(map);
	return true;
}