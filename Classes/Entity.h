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
	void hurtMe(int iHurtValue);
	//是否死亡
	bool isDead();
protected:
	//实体死亡时调用
	virtual void onDead();
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


/*  示例(不基于cocos2d)
const float kMoveSpeed = 2.5f;
const float kAttackRangeSq = 1.5f * 1.5f;
const float kYarnCooldown = 1.0f;

RoboCat::RoboCat() :
    GameObject(),
    mHealth(5),
    mState(RC_IDLE),
    mTargetNetId(0),
    mTimeSinceLastAttack(kYarnCooldown)
{
    SetScale(0.75f);
    SetCollisionRadius(0.6f);
    mSpriteComponent = std::make_shared<SpriteComponent>(this);
    mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("cat"));
}

void RoboCat::WriteForCRC(OutputMemoryBitStream& inStream)
{
    inStream.Write(mPlayerId);
    inStream.Write(mNetworkId);
    inStream.Write(mLocation);
    inStream.Write(mHealth);
    inStream.Write(mState);
    inStream.Write(mTargetNetId);
}

bool RoboCat::MoveToLocation(float inDeltaTime, const Vector3& inLocation)
{
    bool finishedMove = false;

    Vector3 toMoveVec = inLocation - GetLocation();
    float distToTarget = toMoveVec.Length();
    toMoveVec.Normalize2D();
    if (distToTarget > 0.1f)
    {
        if (distToTarget > (kMoveSpeed * inDeltaTime))
        {
            SetLocation(GetLocation() + toMoveVec * inDeltaTime * kMoveSpeed);
        }
        else
        {
            //we're basically almost there, so set it to move location
            SetLocation(inLocation);
            finishedMove = true;
        }
    }
    else
    {
        //since we're close, stop moving towards the target
        finishedMove = true;
    }

    return finishedMove;
}

void RoboCat::UpdateRotation(const Vector3& inTarget)
{
    Vector3 toMoveVec = inTarget - GetLocation();
    toMoveVec.Normalize2D();
    float angle = acosf(Dot2D(toMoveVec, Vector3::NegUnitY));
    Vector3 cross = Cross(Vector3::NegUnitY, toMoveVec);
    if (cross.mZ < 0.0f)
    {
        angle *= -1.0f;
    }
    SetRotation(angle);
}

void RoboCat::EnterMovingState(const Vector3& inTarget)
{
    mMoveLocation = inTarget;

    UpdateRotation(inTarget);

    mState = RC_MOVING;
}

void RoboCat::EnterAttackState(uint32_t inTargetNetId)
{
    mTargetNetId = inTargetNetId;

    //cache the target cat
    GameObjectPtr go = NetworkManager::sInstance->GetGameObject(mTargetNetId);
    //double check this attack target is valid
    if (go && go->GetClassId() == RoboCat::kClassId && go->GetPlayerId() != GetPlayerId())
    {
        mTargetCat = go;
        mState = RC_ATTACK;
    }
    else
    {
        mState = RC_IDLE;
    }
}

void RoboCat::TakeDamage(int inDmgAmount)
{
    mHealth -= inDmgAmount;
    if (mHealth == 0)
    {
        SetDoesWantToDie(true);
    }
}

void RoboCat::HandleDying()
{
    GameObject::HandleDying();
    ScoreBoardManager::sInstance->IncScore(mPlayerId, -1);
}

void RoboCat::Update(float inDeltaTime)
{
    switch (mState)
    {
        case RC_IDLE:
            UpdateIdleState(inDeltaTime);
            break;
        case RC_MOVING:
            UpdateMovingState(inDeltaTime);
            break;
        case RC_ATTACK:
            UpdateAttackState(inDeltaTime);
            break;
    }
}

void RoboCat::UpdateIdleState(float inDeltaTime)
{
    //could do something cute here, like have the cat meow if idle for a while!
    mTimeSinceLastAttack += inDeltaTime;
}

void RoboCat::UpdateMovingState(float inDeltaTime)
{
    mTimeSinceLastAttack += inDeltaTime;
    if (MoveToLocation(inDeltaTime, mMoveLocation))
    {
        //done with the move, so go idle
        mState = RC_IDLE;
    }
}

void RoboCat::UpdateAttackState(float inDeltaTime)
{
    mTimeSinceLastAttack += inDeltaTime;

    if (mTargetCat && !mTargetCat->DoesWantToDie())
    {
        //determine the distance to the target cat
        Vector3 diff = mTargetCat->GetLocation() - mLocation;
        float distSq = diff.LengthSq2D();

        //if we're in yarn cooldown, we aren't allowed to do anything
        if (mTimeSinceLastAttack >= kYarnCooldown)
        {
            UpdateRotation(mTargetCat->GetLocation());
            if (distSq <= kAttackRangeSq)
            {
                //if we're in range, throw a ball of yarn
                mTimeSinceLastAttack = 0.0f;
                GameObjectPtr me = NetworkManager::sInstance->GetGameObject(mNetworkId);
                YarnPtr yarn = std::static_pointer_cast<Yarn>(GameObjectRegistry::sInstance->CreateGameObject('YARN'));
                yarn->InitFromShooter(me, mTargetCat);
            }
            else
            {
                MoveToLocation(inDeltaTime, mTargetCat->GetLocation());
            }
        }
    }
    else
    {
        //target cat is dead
        mTargetCat.reset();
        mState = RC_IDLE;
    }
}
*/