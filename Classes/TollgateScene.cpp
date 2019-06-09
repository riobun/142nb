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


bool TollgateScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

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

	return true;
}

void TollgateScene::update(float dt)
{
    Network::sInstance->Update();
}

void TollgateScene::menuCloseCallback(Ref* pSender)
{
	unscheduleUpdate();
	Director::getInstance()->end();
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
		Hero* mHero = Hero::create();
		mHero->bindSprite(heroSprite);

        //根据是哪边的加英雄
        if (side == 1)
            mHero->setPosition(Point(100, visibleSize.height / 2 + 50));
        else
            mHero->setPosition(Point(visibleSize.width - 100, visibleSize.height / 2 + 50));


		this->addChild(mHero, 1);
		HeroMoveController* heroMoveController = HeroMoveController::create();
		this->addChild(heroMoveController);
		mHero->setController(heroMoveController);

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