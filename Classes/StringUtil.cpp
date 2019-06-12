#include "StringUtil.h"

StringUtil* StringUtil::m_StringUtil = NULL;

StringUtil* StringUtil::getInstance()
{
	if (m_StringUtil == NULL)
	{
		m_StringUtil = new StringUtil();
		if (m_StringUtil && m_StringUtil->init())
		{
			m_StringUtil->autorelease();
			m_StringUtil->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_StringUtil);
			m_StringUtil = NULL;
		}
	}

	return m_StringUtil;
}

bool StringUtil::init()
{

	return true;
}

ValueVector StringUtil::split(const char* srcStr, const char* sSep)
{
	ValueVector stringList;

	int size = strlen(srcStr);

	/* ������ת��Ϊ�ַ������� */
	Value str = Value(srcStr);

	int startIndex = 0;
	int endIndex = 0;
	endIndex = str.asString().find(sSep);

	std::string lineStr;
	/* ���ݻ��з�����ַ���������ӵ��б��� */
	while (endIndex > 0)
	{
		/* ��ȡһ���ַ��� */
		lineStr = str.asString().substr(startIndex, endIndex);

		/* ��ӵ��б� */
		stringList.push_back(Value(lineStr));

		/* ��ȡʣ�µ��ַ��� */
		str = Value(str.asString().substr(endIndex + 1, size));

		endIndex = str.asString().find(sSep);
	}

	/* ʣ�µ��ַ���Ҳ��ӽ��б� */
	if (str.asString().compare("") != 0)
	{
		stringList.push_back(Value(str.asString()));
	}

	return stringList;
}
