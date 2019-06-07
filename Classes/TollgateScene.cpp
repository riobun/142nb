#include"GameHead.h"

Scene* TollgateScene::createScene() {
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);

	
	return scene;
}

void TollgateScene::addHero(Sprite* map) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//��������
	Sprite* heroSprite = Sprite::create("Ashe1.png");
	heroSprite->setScale(SPRITE_SIZE);

	 //�Ѿ���󶨵�Ӣ�۶�����
	Hero* mHero = Hero::create();
	mHero->bindSprite(heroSprite);

	//����Ӣ�۳�����
	mHero->setAnchorPoint(Vec2(0, 0));
	mHero->setPosition(100, visibleSize.height/2 +50);

	this->addChild(mHero);

	//����Ӣ���ƶ�������
	HeroMoveController* heroMoveController = HeroMoveController::create();

	//�ѿ�������ӵ�������
	this->addChild(heroMoveController);

	//���ÿ�������Ӣ������
	mHero->setController(heroMoveController);
}

bool TollgateScene::init() {
	if (!Layer::init())
	{
		return false;

	}

	//��ӵ�ͼ
	auto map = Sprite::create("Map.png");
	map->setScale(1.586f);
	map->setPosition(Point(0, 0));
	map->setAnchorPoint(Vec2(0, 0));
	this->addChild(map,-1);//Ĭ����ӵ�λ�������½�

	addHero(map);
	
	return true;
}