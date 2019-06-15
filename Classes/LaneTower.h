#ifndef _LaneTower_H_
#define _LaneTower_H_

//using namespace cocos2d;
class LaneTower : public Entity {
public:
	void atkCoolDownEnd(float dt);
	CREATE_FUNC(LaneTower);
	virtual bool init();
	int getID();
protected:
	virtual void onDead(int i);

};
#endif // !_LaneTower_H_
