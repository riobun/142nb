#ifndef __ShowNumberNodeTest__NumberSprite__

#define __ShowNumberNodeTest__NumberSprite__

#include"cocos2d.h"

USING_NS_CC;
class NumberSprite:public CCSprite
{
public:

	/*

	 ����һ�����־���

	 ����:

			pTexture: ������������ͼƬ��ͼƬ

			width; ����������ʾ��ͼƬ���

			lenght; ������ʾ�߶�

	*/
	static NumberSprite *CreateNumberSprite(CCTexture2D *pTexture,float width, float lenght);
	/*

  ֱ����ʾ����

  ������

	 num ����ʾ������ͼƬ���

	 isanimation���Ƿ���ʾ����

  */
	
	void f_ShowNumber(int num);

	/*��ʼ��*/
	bool myInit(float width, float length);
	~NumberSprite();


private:
	/*���������ͼƬ��ߣ�������ʾ�������ֻ���ֱ����ʾ����*/
	float s_width;
	float s_length;
};

#endif