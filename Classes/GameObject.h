//  GameObject: ��Ϸ����(����)��ͨ�û���
//  �ο���Multiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ���ģ���õ�� 2019.06.05

/*******��������ʾ��*******
    class RoboCat: public GameObject
    {
        //...
        CLASS_IDENTIFICATION('RBCT', RoboCat)   //�ַ�������(��д)+����
        //...
    };

    ********ע��********
    �þ�������/���٣����ã�HandleDying();
*/

//  ���ʶ
#define CLASS_IDENTIFICATION( inCode, inClass ) \
enum { kClassId = inCode }; \
virtual uint32_t GetClassId() const { return kClassId; } \
static GameObject* CreateInstance() { return static_cast< GameObject* >( new inClass() ); } \

class GameObject
{
public:

	CLASS_IDENTIFICATION( 'GOBJ', GameObject )

	GameObject();
	virtual ~GameObject();

	uint32_t	GetNetworkId()				const				{ return mNetworkId; }
	void		SetNetworkId( uint32_t inNetworkId );

	void		SetPlayerId( uint32_t inPlayerId )			{ mPlayerId = inPlayerId; }
	uint32_t	GetPlayerId()						const 	{ return mPlayerId; }

    void HandleDying();//����Ϸ����(������ʧʱ����)
    //void Update( float inDeltaTime )

	//no default implementation because we don't know what's relevant for each object necessarily
	virtual void		WriteForCRC( OutputMemoryBitStream& inStream )	{ ( void )inStream; }

protected:
    uint32_t										mNetworkId;
    uint32_t										mPlayerId;

};

typedef shared_ptr< GameObject >	GameObjectPtr;

/*  ʾ����
class RoboCat : public GameObject
{
public:
    CLASS_IDENTIFICATION('RCAT', GameObject)

        enum RoboCatState
    {
        RC_IDLE,
        RC_MOVING,
        RC_ATTACK,
    };

    static	GameObjectPtr StaticCreate() { return NetworkManager::sInstance->RegisterAndReturn(new RoboCat()); }

    virtual	RoboCat*	GetAsCat()	override { return this; }

    virtual void Update(float inDeltaTime)	override;
    void UpdateIdleState(float inDeltaTime);
    void UpdateMovingState(float inDeltaTime);
    void UpdateAttackState(float inDeltaTime);
    // returns true if the move is done
    bool MoveToLocation(float inDeltaTime, const Vector3& inLocation);
    void UpdateRotation(const Vector3& inTarget);
    void EnterMovingState(const Vector3& inTarget);
    void EnterAttackState(uint32_t inTargetNetId);
    void TakeDamage(int inDmgAmount);
    virtual void HandleDying() override;

    RoboCat();

    virtual void WriteForCRC(OutputMemoryBitStream& inStream) override;
private:
    Vector3				mMoveLocation;
    SpriteComponentPtr	mSpriteComponent;

    ///move down here for padding reasons...
    int					mHealth;
    RoboCatState		mState;
    uint32_t			mTargetNetId;
    GameObjectPtr		mTargetCat;
    float				mTimeSinceLastAttack;
};

typedef shared_ptr< RoboCat >	RoboCatPtr;
*/