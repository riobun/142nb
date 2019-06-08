#ifndef _MouseInput_H_
#define _MouseInput_H_

#include"GameHead.h"

class MouseInput:public Controller1 {
public:
	CREATE_FUNC(MouseInput);
	virtual bool init();

	void registeMouseEvent();

};


#endif
