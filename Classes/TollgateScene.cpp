#include "GameHead.h"
#include "Art.h"
#include "SimpleAudioEngine.h"
#include "ShopScene.h"
#include "TollgateScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

using namespace cocos2d;

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
		this->addChild(map, -1,map_Tag);
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




	//����Ӣ��
	addHero(map);


	/**
	添加商店按键


	*/
	auto shopItem = MenuItemImage::create(
		"shopButton1.png",
		"shopButton2.png",
		CC_CALLBACK_1(TollgateScene::EnterShop, this));

	if (shopItem == nullptr ||
		shopItem->getContentSize().width <= 0 ||
		shopItem->getContentSize().height <= 0)
	{
		problemLoading("'shopButton1.png' and 'shopButton2.png'");
	}
	else
	{
		shopItem->setScale(0.4f);
		shopItem->setAnchorPoint(Vec2(1,1));
		shopItem->setPosition(visibleSize.width,visibleSize.height);

		
	}	
	// create menu, it's an autorelease object
	auto shopMenu = Menu::create(shopItem, NULL);
	shopMenu->setPosition(Vec2::ZERO);
   	this->addChild(shopMenu, 2);




	////////////////////////////
	//addskillItem
	auto skillItem = CCDirector::sharedDirector()->getWinSize();
	auto menuSkillButton = SkillButton::create("SkillPortrait/Ashe.png", "SkillPortrait/Ashe3.png", 10.f);  //(normal,cool,time)
	menuSkillButton->setPosition(Vec2(0, 0));
	menuSkillButton->setAnchorPoint(Point(0, 0));
	this->addChild(menuSkillButton);





	

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
	//ֹͣ����
	unscheduleUpdate();
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

void TollgateScene::addHero(Sprite* map)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* mHeroSprite = Sprite::create("AShe/Ashe1.png");//��������
	Sprite* eHeroSprite = Sprite::create("AShe/Ashe1.png");
	if (mHeroSprite == nullptr&&eHeroSprite == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		mHeroSprite->setScale(SPRITE_SIZE);
		eHeroSprite->setScale(SPRITE_SIZE);
		//�Ѿ���󶨵�Ӣ�۶�����
		Hero* mHero = Hero::create();
		mHero->bindSprite(mHeroSprite);
		Hero* eHero = Hero::create();
		eHero->bindSprite(eHeroSprite);

		//����Ӣ�۳�����
		mHero->setPosition(Point(100, visibleSize.height / 2 + 50));
		eHero->setPosition(Point(visibleSize.width - 100, visibleSize.height / 2 + 50));

		this->addChild(mHero, 1, mHero_Tag);
		this->addChild(eHero, 1, eHero_Tag);
		//����Ӣ���ƶ�������
		MouseInput* mHeroMoveController = MouseInput::create();
		MouseInput* eHeroMoveController = MouseInput::create();
		//�ѿ��������ӵ�������
		this->addChild(mHeroMoveController);
		this->addChild(eHeroMoveController);
		//���ÿ�������Ӣ������
		mHero->setController(mHeroMoveController);
		eHero->setController(eHeroMoveController);
		
	}

	}
}

void TollgateScene::EnterShop(Ref* pSender)
{
	MenuItem* shopItem = (MenuItem*)pSender;
	log("Touch startItem %p", shopItem);
	auto shopSceneCreate = ShopScene::createScene();

	Director::getInstance()->pushScene(shopSceneCreate);

}
