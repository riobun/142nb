#ifndef _LaneTower_H_
#define _LaneTower_H_

class LaneTower :public Entity {
public:
	CREATE_FUNC(LaneTower);
	virtual bool init();
	int getID();

};
#endif // !_LaneTower_H_
