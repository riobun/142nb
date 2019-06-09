#include "GameHead.h"
#include "Art.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocos2d;

TollgateScene* TollgateScene::slayer;

Scene* TollgateScene::createScene() {
	auto scene = Scene::create();
	slayer = TollgateScene::create();
	scene->addChild(slayer);
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

	//����Ӣ��
    //在网络接收到两方初始化信息后再加英雄,searchFinish()
	//addHero(map, NetworkManager::sInstance->GetMyPlayerId());


	////////////////////////////
	//���Ӽ���ͼ������ȴ
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
		label->setAnchorPoint(Vec2(1.0, 1.0));//�����ӵĴ��룺���ġ�hello world����λ��

		// add the label as a child to this layer
		this->addChild(label, 1);
	}*/


    scheduleUpdate();
	//this->scheduleUpdate();
	//this->scheldue(schedule_selector(HelloWorld::update),1.0f/60);


	return true;
}
void TollgateScene::update(float dt)
{
	//auto label = this->getChildByTag(123);
	//label->setPosition(label->getPosition() + Vec2(2, -2));
    Network::sInstance->Update();
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






void TollgateScene::addHero(Sprite* map, uint32_t side) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* heroSprite = Sprite::create("AShe/Ashe1.png");//��������
	if (heroSprite == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		heroSprite->setScale(SPRITE_SIZE);

		//�Ѿ���󶨵�Ӣ�۶�����
		Hero* mHero = Hero::create();
		mHero->bindSprite(heroSprite);
		//mHero->run(heroSprite);

		//����Ӣ�۳�����

        //根据是哪边的加英雄
        if (side == 1)
            mHero->setPosition(Point(100, visibleSize.height / 2 + 50));
        else
            mHero->setPosition(Point(visibleSize.width - 100, visibleSize.height / 2 + 50));


		this->addChild(mHero, 1);

		//����Ӣ���ƶ�������
		HeroMoveController* heroMoveController = HeroMoveController::create();

		//�ѿ��������ӵ�������
		this->addChild(heroMoveController);

		//���ÿ�������Ӣ������
		mHero->setController(heroMoveController);

        //NetworkManager::sInstance->RegisterAndReturn(mHero);
		
	}




	
}

void TollgateScene::searchFinish()
{
    for (auto &iter : NetworkManager::sInstance->mPlayerNameMap)
    {
        addHero(m_map, iter.first);
    }
    
}