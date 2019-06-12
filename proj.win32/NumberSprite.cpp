#include "NumberSprite.h"

bool NumberSprite::myInit(float width, float length)
{
	s_width = width;
	s_length = length;
	return 1;
}

NumberSprite *NumberSprite::CreateNumberSprite(CCTexture2D*pTexture, float width, float length)
{
	NumberSprite*pobSprite = new NumberSprite();
	if (pobSprite&&pobSprite->initWithTexture(pTexture))
	{
		pobSprite->setVisible(false);
		pobSprite->myInit(width, length);
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
void NumberSprite::f_ShowNumber(int num)
{
	this->setVisible(true);
	this->setTextureRect(CCRectMake(s_width*num, 0, s_width, s_length));
}


NumberSprite::~NumberSprite()
{
}
