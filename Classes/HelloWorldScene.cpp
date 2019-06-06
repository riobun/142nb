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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"




USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
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
bool HelloWorld::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	//tiledMap
	auto map = TMXTiledMap::create("Map/Map2.tmx");
	map->setAnchorPoint(Vec2(-0.5,0.3));
	map->setPosition(Vec2(0, 0));
	map->setGlobalZOrder(-1);
	addChild(map);//Ĭ����ӵ�λ�������½�
	
	
	/////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
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
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));
		label->setAnchorPoint(Vec2(1.0, 1.0));//����ӵĴ��룺���ġ�hello world����λ��

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    

	//this->scheduleUpdate();
	//this->scheldue(schedule_selector(HelloWorld::update),1.0f/60);*/
	

	
	


    return true;
}
void HelloWorld::update(float dt)
{
	auto label = this->getChildByTag(123);
	label->setPosition(label->getPosition() + Vec2(2, -2));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//ֹͣ����
	unscheduleUpdate();
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


Vec2 HelloWorld::toTileCoord(Vec2 position)

{

	auto mapSize = map->getMapSize();        // ��ȡ��tiles����Ϊ��λ�ĵ�ͼ�ߴ�

	// ���㵱ǰ�����£�ÿ����Ƭ�ĳ���
	auto tileWidth = map->getBoundingBox().size.width / map->getMapSize().width;
	auto tileHeight = map->getBoundingBox().size.height / map->getMapSize().height;

	// ��positionת��Ϊ��Ƭ���꣬ȷ���õ���������
    int posx = mapSize.height - position.y / tileHeight + position.x / tileWidth - mapSize.width / 2;
    int posy = mapSize.height - position.y / tileHeight - position.x / tileWidth + mapSize.width / 2;



	return Vec2(posx, posy);

}

// convertToScreenCoord�����е���ѧ��ʽ��ʵ����convertTotileCoord��������ѧԭ���һ�����ƹ�ʽ

Vec2 HelloWorld::toScreenCoord(Vec2 position)

{
	auto mapSize = map->getMapSize();
	auto tileSize = map->getTileSize();
	auto tileWidth = map->getBoundingBox().size.width / map->getMapSize().width;
	auto tileHeight = map->getBoundingBox().size.height / map->getMapSize().height;

	auto variable1 = (position.x + mapSize.width / 2 - mapSize.height) * tileWidth * tileHeight;
	auto variable2 = (-position.y + mapSize.width / 2 + mapSize.height) * tileWidth * tileHeight;

	int posx = (variable1 + variable2) / 2 / tileHeight;
	int posy = (variable2 - variable1) / 2 / tileWidth;



	return Point(posx, posy);

}



