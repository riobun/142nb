#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include"CCNotificationCenter.h"
#include"cocostudio/CocoStudio.h"
#include"GameHead.h"

using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocos2d;

class TollgateDataLayer :public Layer {
public:
	TollgateDataLayer();
	/*{
		m_iMoney = 0;
		m_iKill = 0;
		m_iDeath = 0;
		
	}*/
	~TollgateDataLayer();
	/*{
		NOTIFY->removeAllObservers(this);
	}*/

	/*int m_iMoney;
	int m_iKill;
	int  m_iDeath;

	Text* m_moneyLab;
	Text* m_killLab;
	Text* m_deathLab;*/
	/*void recvRefreshMoney(Ref* pData)
	{
		int iAltValue = (int)pData;
		m_iMoney += iAltValue;
		m_moneyLab->setText(StringUtils::toString(m_iMoney));
	}
	void recvRefreshKill(Ref* pData)
	{
		int iAltValue = (int)pData;
		m_iKill += iAltValue;
		m_killLab->setText(StringUtils::toString(m_iKill));
	}
	void recvRefreshDeath(Ref* pData)
	{
		int iAltValue = (int)pData;
		m_iDeath += iAltValue;
		m_deathLab->setText(StringUtils::toString(m_iDeath));
	}
	*/
	static TollgateDataLayer* dataLayer;
	virtual bool init();
	CREATE_FUNC(TollgateDataLayer);

};
