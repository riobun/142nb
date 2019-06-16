#include "GameHead.h"
#include "Art.h"
#include "SimpleAudioEngine.h"
#include "ShopScene.h"

USING_NS_CC;

using namespace cocos2d;

vector<Entity*> mETT_ptr;
vector<Entity*> eETT_ptr;
Hero* m_hero;
LaneTower* e_laneTower;
Crystal* e_crystal;
bool e_isAtkCoolDown;

double goldenCoin = 0;
double power = 0;
double Ashe_iDenfense = 10;
double Ashe_attackValue = 20;
double PRI_SPEED = 30;

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
	addTower(map);
	int score = 0;
	int testnum = 233;
	auto scoreLb = Label::createWithSystemFont(StringUtils::format("goldenCoin"), "", 32);//    
	scoreLb->setAnchorPoint(Vec2::ZERO);
	scoreLb->setColor(Color3B::YELLOW);
	scoreLb->setPosition(20, Director::getInstance()->getWinSize().height - 515);
	scoreLb->setTag(123);
	this->addChild(scoreLb, 2);
	addNumberNode();

	auto statusBar = Sprite::create("statusBar.png");

	if (statusBar == nullptr)
	{
		problemLoading("Map.png'");
	}
	else
	{
		statusBar->setScale(0.5f);
		// position the sprite on the center of the screen
		statusBar->setPosition(visibleSize.width / 2, 100);
		statusBar->setAnchorPoint(Vec2(0.5, 0.5));
		// add the sprite as a child to this layer
		this->addChild(statusBar, 1);
	}

	

	////////////////////////////
	//���Ӽ���ͼ������ȴ
	auto skillItem = CCDirector::sharedDirector()->getWinSize();
	auto menuSkillQButton = SkillButton::create("SkillPortrait/greenQButton.png", "SkillPortrait/greenQCD.png", 10.f);  //(normal,cool,time)
	menuSkillQButton->setPosition(skillItem.width / 2, skillItem.height / 8+30);
	menuSkillQButton->setScale(0.6f);
	this->addChild(menuSkillQButton,2);

	auto menuSkillWButton = SkillButton::create("SkillPortrait/greenWButton.png", "SkillPortrait/greenWCD.png", 10.f);  //(normal,cool,time)
	menuSkillWButton->setPosition(skillItem.width / 2+90, skillItem.height / 8+30);
	menuSkillWButton->setScale(0.6f);
	this->addChild(menuSkillWButton,2);

	auto menuSkillEButton = SkillButton::create("SkillPortrait/greenEButton.png", "SkillPortrait/greenECD.png", 10.f);  //(normal,cool,time)
	menuSkillEButton->setPosition(skillItem.width / 2+180, skillItem.height / 8+30);
	menuSkillEButton->setScale(0.6f);
	this->addChild(menuSkillEButton,2);



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
		shop->setScale(0.4f);
		shop->setAnchorPoint(Vec2(0,0));
		shop->setPosition(visibleSize.width -90, visibleSize.height-70);


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
	auto label = this->getChildByTag(123);
	label->setPosition(label->getPosition() + Vec2(2, -2));

	goldenCoin += 0.02;
	power += 0.02;
	
	
	if (e_laneTower&&mETT_ptr.size()) {
		for (auto i = 0; i < mETT_ptr.size(); i++) {

			if (mETT_ptr[i]) {
				if ((mETT_ptr[i]->getPosition() - e_laneTower->getPosition()).length() <= tower_attackValue) {

					mETT_ptr[i]->hurtMeHero(i, tower_attackValue, mETT_ptr);
					//tower's attack is cool down

					//e_isAtkCoolDown = true;
					//e_laneTower->scheduleOnce(schedule_selector(LaneTower::atkCoolDownEnd), 1.0f);
				}
			}
		}
	}
		
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


void TollgateScene::addHero(Sprite* map) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* mHeroSprite = Sprite::create("greenHero.png");
	Sprite* eHeroSprite = Sprite::create("greenHero.png");
	
	if (mHeroSprite == nullptr && eHeroSprite == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{

		mHeroSprite->setScale(SPRITE_SIZE);
		eHeroSprite->setScale(SPRITE_SIZE);

		Hero* mHero = Hero::create();	
		
		mHero->bindSprite(mHeroSprite);
		mHero->run();
		mETT_ptr.push_back(mHero);
	
		Hero* eHero = Hero::create();
		eHero->bindSprite(eHeroSprite);
		eHero->run();
		eETT_ptr.push_back(eHero);

		mHero->setPosition(Point(100, visibleSize.height / 2 + 50));
		eHero->setPosition(Point(visibleSize.width - 100, visibleSize.height / 2 + 50));


		this->addChild(mHero, 1);
		this->addChild(eHero, 1);

		Point cur_pos = Point(visibleSize.width - 100, visibleSize.height / 2 + 50);
		double iTime = (cur_pos - Vec2(visibleSize.width / 2, visibleSize.height / 2)).length() / PRI_SPEED;
		MoveTo* moveTo = MoveTo::create(iTime, Vec2(visibleSize.width / 2, visibleSize.height / 2));
		eHero->runAction(moveTo);
		
		
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
	m_laneTower = mLaneTower;

	//build enemy's tower
	Sprite* eLaneTowerSprite = Sprite::create("tower.png");
	LaneTower* eLaneTower = LaneTower::create();
	eLaneTower->bindSprite(eLaneTowerSprite);
	eLaneTower->setPosition(Point(visibleSize.width * 3 / 4 - 60, visibleSize.height / 2 + 15));
	this->addChild(eLaneTower, 1);
	eETT_ptr.push_back(eLaneTower);
	
	//build my cystal
	Sprite* mCrystalSprite = Sprite::create("crystal.png");
	mCrystalSprite->setScale(Crystal_SIZE);
	Crystal* mCrystal = Crystal::create();
	mCrystal->bindSprite(mCrystalSprite);
	mCrystal->setPosition(Point(visibleSize.width  / 5 - 15, visibleSize.height / 2 + 30));
	this->addChild(mCrystal, 1, 1);
	mETT_ptr.push_back(mCrystal);
	m_crystal = mCrystal;

	//build enemy's cystal
	Sprite* eCrystalSprite = Sprite::create("crystal.png");
	eCrystalSprite->setScale(Crystal_SIZE);
	
	Crystal* eCrystal = Crystal::create();
	
	eCrystal->bindSprite(eCrystalSprite);
	
	eCrystal->setPosition(Point(visibleSize.width  * 4 / 5 + 15, visibleSize.height / 2 + 30));
	
	this->addChild(eCrystal, 1);
	e_crystal = eCrystal;
	eETT_ptr.push_back(eCrystal);

}

void TollgateScene::shop(Ref* pSender)
{
	MenuItem* shop = (MenuItem*)pSender;
	log("Touch backGame %p", shop);
	auto toShopScene = ShopScene::createScene();

	Director::getInstance()->pushScene(toShopScene);

}

void TollgateScene::addNumberNode()
{
	ShowNumberNode * snn = ShowNumberNode::CreateShowNumberNode("score_num.png", 10000, 28, 33);
	snn->f_ShowNumber(goldenCoin);
	snn->setPosition(ccp(100, 100));
	this->addChild(snn, 0, 0);
	schedule(schedule_selector(TollgateScene::logic), 2.0f);

}

void TollgateScene::logic(float dt)
{
	ShowNumberNode*snn = (ShowNumberNode *)this->getChildByTag(0);
	snn->f_ShowNumber(goldenCoin);
	goldenCoin += 1;
	power += 1;
}
