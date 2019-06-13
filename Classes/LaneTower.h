#ifndef _LaneTower_H_
#define _LaneTower_H_

class LaneTower :public Entity {
public:
	void atkCoolDownEnd(float dt);
	CREATE_FUNC(LaneTower);
	virtual bool init();
	int getID();
	

protected:
	virtual void onDead(int i, vector<Entity*> ETT_ptr);

};
#endif // !_LaneTower_H_
