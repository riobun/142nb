#ifndef _Entity_H_
#define _Entity_H_

#define CLASS_IDENTIFICATION( inCode, inClass ) \
enum { kClassId = inCode }; \
virtual uint32_t GetClassId() const { return kClassId; } \
static Entity* CreateInstance() { return static_cast< Entity* >( new inClass() ); } \

class Hero;
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

	//被攻击
	void hurtMe(int i,int iHurtValue, vector<Entity*> ETT_ptr);
	//是否死亡
	bool isDead();
protected:
	//实体死亡时调用
	virtual void onDead(int i, vector<Entity*> ETT_ptr);
	//绑定精灵时调用
	virtual void onBindSprite();
	//受伤害时调用
	virtual void onHurt();
protected:
    cocos2d::Sprite* m_sprite;
	Controller1* m_controller;
	
    uint32_t		mNetworkId; //每个实体都有唯一的网络id，在各玩家处都相同
    uint32_t		mPlayerId;      //这个实体是属于哪个玩家的
	
	CC_SYNTHESIZE(int, m_ID, ID);              //实体ID
	CC_SYNTHESIZE(int, m_iModelID, iModelID);//模型ID
	CC_SYNTHESIZE(std::string, m_sName, sName);//名字
	CC_SYNTHESIZE(int, m_iHP, iHP);            //HP
	CC_SYNTHESIZE(int, m_iDefense, iDefense);  //防御
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);      //移速
	CC_SYNTHESIZE(int, m_iLevel, iLevel);      //等级
	bool m_isDead;                             //标记是否死亡
	
};
typedef std::shared_ptr< Entity > EntityPtr;
#endif
