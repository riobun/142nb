#ifndef _Entity_H_
#define _Entity_H_

#define CLASS_IDENTIFICATION( inCode, inClass ) \
enum { kClassId = inCode }; \
virtual uint32_t GetClassId() const { return kClassId; }  \
static Entity* CreateInstance() { return static_cast< Entity* >( new inClass() ); }   \

class Hero;
class Soilder;
class Controller1;
class OutputMemoryBitStream;
//class ControllerListener;

class Entity :public ControllerListener{
public:
	Entity();
	~Entity();

    CLASS_IDENTIFICATION('ENTT', Entity);

    uint32_t	GetNetworkId()				const { return mNetworkId; }
    void		SetNetworkId(uint32_t inNetworkId);

    void		SetPlayerId(uint32_t inPlayerId) { mPlayerId = inPlayerId; }
    uint32_t	GetPlayerId()						const { return mPlayerId; }
    virtual void		WriteForCRC(OutputMemoryBitStream& inStream) { (void)inStream; }

    void bindSprite(cocos2d::Sprite* sprite);

	void setController(Controller1* controller);

	virtual void setTagPosition(int x, int y);
	virtual cocos2d::Point getTagPosition();
	
    cocos2d:: Sprite* getSprite();

	//������
	void hurtMe(int i,int iHurtValue, vector<Entity*> ETT_ptr);
	
	void hurtMeHero(int i, int iHurtValue, vector<Entity*> iETT_ptr);
	//�Ƿ�����
	bool isDead();
protected:
	//ʵ������ʱ����
	virtual void onDead(int i);
	virtual void mHero_onDead(int i);
	//�󶨾���ʱ����
	virtual void onBindSprite();
	//���˺�ʱ����
	virtual void onHurt();
protected:
    cocos2d::Sprite* m_sprite;
	Controller1* m_controller;
	
    uint32_t		mNetworkId; //ÿ��ʵ�嶼��Ψһ������id���ڸ���Ҵ�����ͬ
    uint32_t		mPlayerId;      //���ʵ���������ĸ���ҵ�
	
	CC_SYNTHESIZE(int, m_ID, ID);              //ʵ��ID
	CC_SYNTHESIZE(int, m_iModelID, iModelID);//ģ��ID
	CC_SYNTHESIZE(std::string, m_sName, sName);//����
	CC_SYNTHESIZE(int, m_iHP, iHP);            //HP
	CC_SYNTHESIZE(int, m_iDefense, iDefense);  //����
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);      //����
	CC_SYNTHESIZE(int, m_iLevel, iLevel);      //�ȼ�
	bool m_isDead;                             //����Ƿ�����
	
};
typedef std::shared_ptr< Entity > EntityPtr;
#endif
