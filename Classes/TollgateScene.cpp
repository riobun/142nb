#include"GameHead.h"

using namespace cocos2d;

Scene* TollgateScene::createScene() {
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);
	return scene;
}

void TollgateScene::addHero(Sprite* map) {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��������
	Sprite* heroSprite = Sprite::create("Ashe1.png");
	heroSprite->setScale(SPRITE_SIZE);

	 //�Ѿ���󶨵�Ӣ�۶�����
	Hero* mHero = Hero::create();
	mHero->bindSprite(heroSprite);
	mHero->run(heroSprite);

	//����Ӣ�۳�����
	mHero->setPosition(Point(50, visibleSize.height / 2));

	map->addChild(mHero);

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
	auto map = Sprite::create("map.png");
	this->addChild(map);//Ĭ����ӵ�λ�������½�

	addHero(map);
	return true;
}