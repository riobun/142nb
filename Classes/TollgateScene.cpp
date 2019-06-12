#include "GameHead.h"
#include "Art.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "ShopScene.h"

USING_NS_CC;

using namespace cocos2d;

TollgateScene* TollgateScene::slayer;

Scene* TollgateScene::createScene() {
	auto scene = Scene::create();
	slayer = TollgateScene::create();
	scene->addChild(slayer);
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}

TollgateScene::TollgateScene()
{

}

TollgateScene::~TollgateScene()
{

}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool TollgateScene::init()
{
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
    m_map = map;
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

	auto shieldLayer = Sprite::create("shieldLayer.png");  // shieldLayerΪ���β�
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

    Network::StaticInit(default_name);
    EntityRegistry::StaticInit();
    EntityRegistry::sInstance->RegisterCreationFunction('HERO', Hero::StaticCreate);

    //在网络接收到两方初始化信息后再加英雄,searchFinish()

	auto skillItem = CCDirector::sharedDirector()->getWinSize();
	auto menuSkillButton = SkillButton::create("SkillPortrait/Ashe.png", "SkillPortrait/Ashe3.png", 2.f);  //(normal,cool,time)
	menuSkillButton->setPosition(skillItem.width / 2, skillItem.height / 2);
	this->addChild(menuSkillButton);
	//���Ӣ��
	addHero(map);
	addTower(map);
	

	////////////////////////////
	//��Ӽ���ͼ������ȴ
	auto skillItem = CCDirector::sharedDirector()->getWinSize();
	auto menuSkillButton = SkillButton::create("SkillPortrait/Ashe.png", "SkillPortrait/Ashe3.png", 10.f);  //(normal,cool,time)
	menuSkillButton->setPosition(skillItem.width / 2, skillItem.height / 2);
	this->addChild(menuSkillButton);






	auto shop = MenuItemImage::create(
		"shopButton1.png",
		"shopButton2.png",
		CC_CALLBACK_1(TollgateScene::shop, this));

	if (shop == nullptr ||
		shop->getContentSize().width <= 0 ||
		shop->getContentSize().height <= 0)
	{
		problemLoading("'shopButton1.png' and 'shopButton2.png'");
	}
	else
	{
		shop->setScale(0.2f);
		shop->setAnchorPoint(Vec2(0, 0));
		shop->setPosition(visibleSize.width / 10, visibleSize.height / 7 - 10);


	}
	// create menu, it's an autorelease object
	auto shopMenu = Menu::create(shop, NULL);
	shopMenu->setPosition(Vec2::ZERO);
	this->addChild(shopMenu, 2);



	

	//this->scheduleUpdate();
	//this->scheldue(schedule_selector(HelloWorld::update),1.0f/60);


	return true;
}

void TollgateScene::update(float dt)
{
    Network::sInstance->Update();
}

void TollgateScene::menuCloseCallback(Ref* pSender)
{
	//ֹͣ����
	unscheduleUpdate();
	Director::getInstance()->end();
}


void TollgateScene::addHero(Sprite* map) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* mHeroSprite = Sprite::create("AShe/Ashe1.png");
	//Sprite* eHeroSprite = Sprite::create("AShe/Ashe1.png");
	if (mHeroSprite == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{

		mHeroSprite->setScale(SPRITE_SIZE);
		//eHeroSprite->setScale(SPRITE_SIZE);

		//�Ѿ���󶨵�Ӣ�۶�����

		Hero* mHero = Hero::create();
		mHero->bindSprite(mHeroSprite);
		//Hero* eHero = Hero::create();
		//eHero->bindSprite(eHeroSprite);

		//����Ӣ�۳�����
		mHero->setPosition(Point(100, visibleSize.height / 2 + 50));
		//eHero->setPosition(Point(visibleSize.width - 100, visibleSize.height / 2 + 50));


		this->addChild(mHero, 1);
		//this->addChild(eHero, 1, eHero_Tag);
		
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

	Sprite* mLaneTowerSprite = Sprite::create("tower.png");
	LaneTower* mLaneTower = LaneTower::create();
	mLaneTower->bindSprite(mLaneTowerSprite);
	mLaneTower->setPosition(Point(visibleSize.width * 3 / 4 - 60, visibleSize.height / 2 + 15));
	this->addChild(mLaneTower, 1);

}


void TollgateScene::shop(Ref* pSender)
{
	MenuItem* shop = (MenuItem*)pSender;
	log("Touch backGame %p", shop);
	auto toShopScene = ShopScene::createScene();

	Director::getInstance()->pushScene(toShopScene);

        NetworkManager::sInstance->RegisterAndReturn(mHero);
		
	}
}

void TollgateScene::searchFinish()
{
    for (auto &iter : NetworkManager::sInstance->mPlayerNameMap)
    {
        addHero(m_map, iter.first);
    }
    
}