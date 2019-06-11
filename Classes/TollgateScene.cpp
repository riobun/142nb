#include "GameHead.h"
#include "Art.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;

vector<Entity*> mETT_ptr;
vector<Entity*> eETT_ptr;

Scene* TollgateScene::createScene() {
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}






static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TollgateScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object

	auto map = Sprite::create("Map.png");
	
	if (map == nullptr)
	{
		problemLoading("Map.png'");
	}
	else
	{
		map->setScale(1.586f);
		// position the sprite on the center of the screen
		map->setPosition(Point(0, 0));
		map->setAnchorPoint(Vec2(0, 0));
		// add the sprite as a child to this layer
		this->addChild(map, -1);
	}

	auto shieldLayer = Sprite::create("shieldLayer.png");  // shieldLayer为屏蔽层
	if (shieldLayer == nullptr)
	{
		problemLoading("shieldLayer.png'");
	}
	else
	{
		shieldLayer->setScale(1.586f);
		// position the sprite on the center of the screen
		shieldLayer->setPosition(Point(0, 0));
		shieldLayer->setAnchorPoint(Vec2(0, 0));
		// add the sprite as a child to this layer
		this->addChild(shieldLayer, 0);
	}

	//添加英雄
	addHero(map);
	addTower(map);
	

	////////////////////////////
	//添加技能图标与冷却
	auto skillItem = CCDirector::sharedDirector()->getWinSize();
	auto menuSkillButton = SkillButton::create("SkillPortrait/Ashe.png", "SkillPortrait/Ashe3.png", 2.f);  //(normal,cool,time)
	menuSkillButton->setPosition(skillItem.width / 2, skillItem.height / 2);
	this->addChild(menuSkillButton);



	/*auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	label->setTag(123);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));
		label->setAnchorPoint(Vec2(1.0, 1.0));//新添加的代码：更改“hello world”的位置

		// add the label as a child to this layer
		this->addChild(label, 1);
	}*/



	//this->scheduleUpdate();
	//this->scheldue(schedule_selector(HelloWorld::update),1.0f/60);


	return true;
}
void TollgateScene::update(float dt)
{
	auto label = this->getChildByTag(123);
	label->setPosition(label->getPosition() + Vec2(2, -2));
}

void TollgateScene::menuCloseCallback(Ref* pSender)
{
	//停止更新
	unscheduleUpdate();
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}


void TollgateScene::addHero(Sprite* map) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* mHeroSprite = Sprite::create("AShe/Ashe1.png");
	Sprite* eHeroSprite = Sprite::create("AShe/Ashe1.png");
	
	if (mHeroSprite == nullptr && eHeroSprite == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{

		mHeroSprite->setScale(SPRITE_SIZE);
		eHeroSprite->setScale(SPRITE_SIZE);

		//把精灵绑定到英雄对象上

		Hero* mHero = Hero::create();
		mHero->bindSprite(mHeroSprite);
		Hero* eHero = Hero::create();
		eHero->bindSprite(eHeroSprite);
		eETT_ptr.push_back(eHero);

		//设置英雄出生点
		mHero->setPosition(Point(100, visibleSize.height / 2 + 50));
		eHero->setPosition(Point(visibleSize.width - 100, visibleSize.height / 2 + 50));


		this->addChild(mHero, 1);
		this->addChild(eHero, 1);
		
		
		HeroMoveController* mHeroMoveController = HeroMoveController::create();
		//HeroMoveController* eHeroMoveController = HeroMoveController::create();
		
		this->addChild(mHeroMoveController);
		//this->addChild(eHeroMoveController);
		
		mHero->setController(mHeroMoveController);
		//eHero->setController(eHeroMoveController);

		
	}

	
}

void TollgateScene::addTower(Sprite* map) { 
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//build my tower
	Sprite* mLaneTowerSprite = Sprite::create("tower.png");
	LaneTower* mLaneTower = LaneTower::create();
	mLaneTower->bindSprite(mLaneTowerSprite);
	mLaneTower->setPosition(Point(visibleSize.width / 4 + 60, visibleSize.height / 2 + 15));
	this->addChild(mLaneTower, 1);
	mETT_ptr.push_back(mLaneTower);

	//build enemy's tower
	Sprite* eLaneTowerSprite = Sprite::create("tower.png");
	LaneTower* eLaneTower = LaneTower::create();
	eLaneTower->bindSprite(eLaneTowerSprite);
	eLaneTower->setPosition(Point(visibleSize.width * 3 / 4 - 60, visibleSize.height / 2 + 15));
	this->addChild(eLaneTower, 1);
	eETT_ptr.push_back(eLaneTower);
	
	//build my cystal
	Sprite* mCystalSprite = Sprite::create("crystal.png");
	mCystalSprite->setScale(Cystal_SIZE);
	LaneTower* mCystal = LaneTower::create();
	mCystal->bindSprite(mCystalSprite);
	mCystal->setPosition(Point(visibleSize.width  / 5 - 15, visibleSize.height / 2 + 30));
	this->addChild(mCystal, 1, 1);
	mETT_ptr.push_back(mCystal);

	//build enemy's cystal
	Sprite* eCystalSprite = Sprite::create("crystal.png");
	eCystalSprite->setScale(Cystal_SIZE);
	LaneTower* eCystal = LaneTower::create();
	eCystal->bindSprite(eCystalSprite);
	eCystal->setPosition(Point(visibleSize.width  * 4 / 5 + 15, visibleSize.height / 2 + 30));
	this->addChild(eCystal, 1);
	eETT_ptr.push_back(eCystal);



}

