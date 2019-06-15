#include "GameHead.h"
#include "WelcomeScene.h"
#include "SimpleAudioEngine.h"



USING_NS_CC;

Scene* WelcomeScene::createScene()
{
	return WelcomeScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool WelcomeScene::init()
{
	//////////////////////////////
	// 1. super init first
	/*if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = TMXTiledMap::create("Map/Map.tmx");
	addChild(tileMap, 0, 100);
	*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = Sprite::create("background.png");
	if (backGround == nullptr)
	{
		problemLoading("'background.png'");
	}
	else
	{
		backGround->setScale(1.586f);
		// position the sprite on the center of the screen
		backGround->setPosition(Point(0, 0));
		backGround->setAnchorPoint(Vec2(0, 0));
		// add the sprite as a child to this layer
		this->addChild(backGround, -1);
	}

	auto Logo = Sprite::create("Logo.png");
	Logo->setScale(0.8f);
	Logo->setPosition(visibleSize.width / 2, visibleSize.height * 3/ 5);
	addChild(Logo, 1);


	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto startItem = MenuItemImage::create(
		"Start1.png",
		"Start2.png",
		CC_CALLBACK_1(WelcomeScene::EnterTollgateScene, this));

	if (startItem == nullptr ||
		startItem->getContentSize().width <= 0 ||
		startItem->getContentSize().height <= 0)
	{
		problemLoading("'Start1.png' and 'Start2.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - startItem->getContentSize().width / 2;
		float y = origin.y + startItem->getContentSize().height / 2;
		startItem->setScale(0.4f);
		startItem->setAnchorPoint(Vec2(0,0));
		startItem->setPosition(500,150);
		
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 0);






	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "HelloWorld" splash screen"
	

	
	return true;
}

void WelcomeScene::EnterTollgateScene(Ref* pSender)
{
	MenuItem* startItem = (MenuItem*)pSender;
	log("Touch startItem %p", startItem);
	auto tollgateSceneCreate = TollgateScene::createScene();

	Director::getInstance()->pushScene(tollgateSceneCreate);

}
