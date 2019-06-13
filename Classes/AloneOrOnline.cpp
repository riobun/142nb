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

#include "AloneOrOnline.h"
#include "SimpleAudioEngine.h"




USING_NS_CC;

Scene* AOO::createScene()
{
	auto scene = Scene::create();
	auto layer = AOO::create();
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
bool AOO::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	CCLabelTTF* standAlone = CCLabelTTF::create("Stand-Alone", "Marker Felt", 30);	
		
	CCLabelTTF* online = CCLabelTTF::create("Online", "Marker Felt", 30);	

	CCMenuItemLabel* mAlone = CCMenuItemLabel::create(standAlone, this, menu_selector(AOO::standAlone));
	mAlone->setPosition(ccp(visibleSize.width / 2, 250));
	CCMenuItemLabel* mOnline = CCMenuItemLabel::create(online, this, menu_selector(AOO::online));	
	mOnline->setPosition(ccp(visibleSize.width / 2, 50));	
	CCMenu* choose = CCMenu::create(mAlone, mOnline, NULL);
	choose->setPosition(ccp(0, 0));	this->addChild(choose);

	




	//this->scheduleUpdate();
	//this->scheldue(schedule_selector(HelloWorld::update),1.0f/60);*/


	return true;
}



void AOO::update(float dt)
{
	auto label = this->getChildByTag(123);
	label->setPosition(label->getPosition() + Vec2(2, -2));
}


void AOO::standAlone(Ref* pSender)
{
	MenuItem* standAlone = (MenuItem*)pSender;
	log("Touch alone %p", standAlone);
	auto chooseAlone = AOO::createScene();

	Director::getInstance()->pushScene(chooseAlone);

}



void AOO::online(Ref* pSender)
{
	MenuItem* online = (MenuItem*)pSender;
	auto chooseOnline = AOO::createScene();

	Director::getInstance()->pushScene(chooseOnline);

}




