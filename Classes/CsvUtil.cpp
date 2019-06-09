#include "CsvUtil.h"
#include "StringUtil.h"

CsvUtil* CsvUtil::m_CsvUtil = NULL;

CsvUtil* CsvUtil::getInstance() {
	if (m_CsvUtil == NULL) {
		m_CsvUtil = new CsvUtil();
		if (m_CsvUtil && m_CsvUtil->init()) {
			m_CsvUtil->autorelease();
			m_CsvUtil->retain();
		}
		else {
			CC_SAFE_DELETE(m_CsvUtil);
			m_CsvUtil = NULL;
		}
	}

	return m_CsvUtil;
}

bool CsvUtil::init() {
	return true;
}

void CsvUtil::loadFile(const char* sPath) {

	/* ���һ��csv�ļ��Ķ��� */
	CsvData* csvData = CsvData::create();

	/* ��ȡ���ݣ����б��浽�б��� */
	std::string str = FileUtils::getInstance()->getStringFromFile(sPath);
	ValueVector linesList = StringUtil::getInstance()->split(str.c_str(), "\n");

	/* ��ÿһ�е��ַ�����ֳ����������ŷָ��� */
	for (auto value : linesList) {
		/*
			��һ�е��ַ��������ŷָ���Ȼ���ŵ��б��У�����б��ŵ�CsvData�����
			���仰˵��csvData����Ϊһ����ά��񣬼�¼�������ļ��к��е��ַ���
		*/
		ValueVector tArr = StringUtil::getInstance()->split(value.asString().c_str(), ",");
		csvData->addLineData(tArr);
	}

	/* ����б��ֵ��� */
	mCsvMap.insert(sPath, csvData);
}

Value CsvUtil::getValue(int iRow, int iCol, const char* csvFilePath) {
	/* ȡ��Csv�ļ����� */
	auto csvData = mCsvMap.at(csvFilePath);

	/* ��������ļ������ݲ����ڣ�����������ļ� */
	if (csvData == nullptr) {
		loadFile(csvFilePath);
		csvData = mCsvMap.at(csvFilePath);
	}
	Size size = csvData->getRowColNum();

	/* �������� */
	int iRowNum = size.width;
	int iColNum = size.height;

	/* �±�Խ�� */
	if (iRow >= iRowNum || iCol >= iColNum) {
		return Value("");
	}

	/* ��ȡ��iRow������ */
	ValueVector rowVector = csvData->getSingleLineData(iRow);

	/* ��ȡ��iCol������ */
	Value colValue = rowVector.at(iCol);

	return colValue;
}

const std::string CsvUtil::get(int iRow, int iCol, const char* csvFilePath) {
	Value colValue = getValue(iRow, iCol, csvFilePath);

	return colValue.asString();
}

const Size CsvUtil::getFileRowColNum(const char* csvFilePath)
{
	/* ȡ�������ļ��Ķ�ά��� */
	auto csvData = mCsvMap.at(csvFilePath);

	/* ��������ļ������ݲ����ڣ�����������ļ� */
	if (csvData == nullptr) {
		loadFile(csvFilePath);
		csvData = mCsvMap.at(csvFilePath);
	}
	Size size = csvData->getRowColNum();
	return size;
}

const int CsvUtil::getInt(int iRow, int iCol, const char* csvFilePath) {
	Value colValue = getValue(iRow, iCol, csvFilePath);
	return colValue.asInt();
}

const float CsvUtil::getFloat(int iRow, int iCol, const char* csvFilePath) {
	Value colValue = getValue(iRow, iCol, csvFilePath);

	return colValue.asFloat();
}

const bool CsvUtil::getBool(int iRow, int iCol, const char* csvFilePath)
{
	Value colValue = getValue(iRow, iCol, csvFilePath);
	return colValue.asBool();
}

const int CsvUtil::findValueInWithLine(const char* chValue, int iValueCol, const char* csvFilePath) {
	Size csvSize = getFileRowColNum(csvFilePath);

	int iLine = -1;
	for (int i = 2; i < csvSize.width; i++) {
		int ID = getInt(i, iValueCol, csvFilePath);
		if (Value(ID).asString().compare(chValue) == 0) {
			iLine = i;
			break;
		}
	}

	return iLine;
}
