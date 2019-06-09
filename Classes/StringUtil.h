#ifndef StringUtil_H
#define StringUtil_H

#include "cocos2d.h"

using namespace cocos2d;

class StringUtil : public Ref {
public:
	static StringUtil* getInstance();
	virtual bool init();

	/* 用分隔符分割字符串，结果存放到一个列表中，列表中的对象为Value */
	ValueVector split(const char* srcStr, const char* sSep);
private:
	static StringUtil* m_StringUtil;

};

#endif
