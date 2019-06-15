#ifndef _Crystal_H_
#define _Crystal_H_

#include"GameHead.h"
using namespace cocos2d;

class Crystal : public Entity {
public:
	CREATE_FUNC(Crystal);
	virtual bool init();
	int getID();

};

#endif // !_Crystal_H_

