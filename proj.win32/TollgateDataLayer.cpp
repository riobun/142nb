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
	//��Ǯ
	/*m_moneyLab = (Text*)Helper::seekWidgetByName(UI, "moneyLab");
	//��ɱ��
	m_killLab = (Text*)Helper::seekWidgetByName(UI, "killLab");
	//������
	m_deathLab = (Text*)Helper::seekWidgetByName(UI, "deathLab");

	//������Ϣ
	NOTIFY->addObserver(this, callfuncO_selector(TollgateDataLayer::recvRefreshMoney), "MoneyChange", NULL);
	NOTIFY->addObserver(this, callfuncO_selector(TollgateDataLayer::recvRefreshKill), "KillChange", NULL);
	NOTIFY->addObserver(this, callfuncO_selector(TollgateDataLayer::recvRefreshDeath), "DeathChange", NULL);
	*/
	return true;
}