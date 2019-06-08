#ifndef _HeroMoveController_H_
#define _HeroMoveController_H_

class HeroMoveController :public Controller1 {
public:
	CREATE_FUNC(HeroMoveController);
	virtual bool init();
	double HeroSpeed;

	void registeMouseEvent();
};



#endif // !_HeroMoveController_H_
