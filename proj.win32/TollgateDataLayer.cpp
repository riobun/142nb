#include "TollgateDataLayer.h"

TollgateDataLayer::TollgateDataLayer() {

}
TollgateDataLayer::~TollgateDataLayer() {

}

bool TollgateDataLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//loading UI
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("TollgateUI.Json");
	this->addChild(UI);
	UI->setTouchEnabled(false);
	//金钱
	/*m_moneyLab = (Text*)Helper::seekWidgetByName(UI, "moneyLab");
	//击杀数
	m_killLab = (Text*)Helper::seekWidgetByName(UI, "killLab");
	//死亡数
	m_deathLab = (Text*)Helper::seekWidgetByName(UI, "deathLab");

	//订阅消息
	NOTIFY->addObserver(this, callfuncO_selector(TollgateDataLayer::recvRefreshMoney), "MoneyChange", NULL);
	NOTIFY->addObserver(this, callfuncO_selector(TollgateDataLayer::recvRefreshKill), "KillChange", NULL);
	NOTIFY->addObserver(this, callfuncO_selector(TollgateDataLayer::recvRefreshDeath), "DeathChange", NULL);
	*/
	return true;
}