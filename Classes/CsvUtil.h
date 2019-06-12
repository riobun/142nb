
#ifndef CsvUtil_H
#define CsvUtil_H

#include "cocos2d.h"
#include "CsvData.h"

using namespace cocos2d;

class CsvUtil : public Ref {
public:
	/* ��ȡ���߶��� */
	static CsvUtil* getInstance();

	virtual bool init();

	/* ���������ļ� */
	void loadFile(const char* sPath);

	/* ��ȡĳ��ĳ�е�ֵ */
	Value getValue(int iRow, int iCol, const char* csvFilePath);

	/* ��ȡĳ��ĳ�е�ֵ����ת��Ϊ�ַ��� */
	const std::string get(int iRow, int iCol, const char* csvFilePath);

	/* ��ȡĳ��ĳ�е�ֵ������ת��Ϊ���� */
	const int getInt(int iRow, int iCol, const char* csvFilePath);

	/* ��ȡĳ��ĳ�е�ֵ������ת��Ϊ������ */
	const float getFloat(int iRow, int iCol, const char* csvFilePath);

	/* ��ȡĳ��ĳ�е�ֵ������ת��Ϊ������ */
	const bool getBool(int iRow, int iCol, const char* csvFilePath);

	/* ��ȡ�����ļ����ݵ��к������� */
	const Size getFileRowColNum(const char* csvFilePath);

	/* ����ĳ���е�ֵ�����Ҹ�ֵ���ڵ��� */
	const int findValueInWithLine(const char* chValue, int iValueCol, const char* csvFilePath);
private:
	static CsvUtil* m_CsvUtil;

	/* ���mCsvStrList-filePath���ֵ� */
	Map<std::string, CsvData*> mCsvMap;
};

#endif
