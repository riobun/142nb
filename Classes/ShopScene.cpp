/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameHead.h"
#include "ShopScene.h"
#include "SimpleAudioEngine.h"
#include "Equipment.h"
#include "GameHead.h"



USING_NS_CC;

Scene* ShopScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ShopScene::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ShopScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto shopBackground = Sprite::create("shopBackground.png");
	if (shopBackground == nullptr)
	{
		problemLoading("'shopBackground.png'");
	}
	else
	{
		shopBackground->setScale(1.586f);
		// position the sprite on the center of the screen
		shopBackground->setPosition(Point(0, 0));
		shopBackground->setAnchorPoint(Vec2(0, 0));
		// add the sprite as a child to this layer
		this->addChild(shopBackground, -1);
	}


	auto backGame = MenuItemImage::create(
		"backGame1.png",
		"backGame2.png",
		CC_CALLBACK_1(ShopScene::backGame, this));

	if (backGame == nullptr ||
		backGame->getContentSize().width <= 0 ||
		backGame->getContentSize().height <= 0)
	{
		problemLoading("'backGame1.png' and 'backGame2.png'");
	}
	else
	{
		backGame->setScale(0.2f);
		backGame->setAnchorPoint(Vec2(0, 0));
		backGame->setPosition(visibleSize.width/10, visibleSize.height/7-10);


	}
	// create menu, it's an autorelease object
	auto backGameMenu = Menu::create(backGame, NULL);
	backGameMenu->setPosition(Vec2::ZERO);
	this->addChild(backGameMenu, 2);




	/**
	���װ��
	*/
	auto speedUpButton = Equipment::create("Equipment/speedUp.png",
		"Equipment/speedUpCD.png",
		"speedUpBuff");
	speedUpButton->setPosition(visibleSize.width / 7, visibleSize.height / 3 * 2);
	this->addChild(speedUpButton);


	auto attackButton = Equipment::create("Equipment/attack.png",
		"Equipment/attackCD.png",
		"attackBuff");
	attackButton->setPosition(visibleSize.width / 7+100, visibleSize.height / 3 * 2);
	this->addChild(attackButton);


	auto defenseButton = Equipment::create("Equipment/defense.png",
		"Equipment/defenseCD.png",
		"defenseBuff");
	defenseButton->setPosition(visibleSize.width / 7+200, visibleSize.height / 3 * 2);
	this->addChild(defenseButton);



	return true;
}

void ShopScene::backGame(Ref* pSender)
{
	MenuItem* backGame = (MenuItem*)pSender;
	log("Touch backGame %p", backGame);
	auto backTollgateScene = TollgateScene::createScene();

	Director::getInstance()->pushScene(backTollgateScene);

}

void ShopScene::update(float dt)
{
	auto label = this->getChildByTag(123);
	label->setPosition(label->getPosition() + Vec2(2, -2));
}

void ShopScene::menuCloseCallback(Ref* pSender)
{
	//stopUpdate
	unscheduleUpdate();
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}



