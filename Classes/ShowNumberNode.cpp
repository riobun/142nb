
#include "GameHead.h"


ShowNumberNode*ShowNumberNode::CreateShowNumberNode(const char *path, int numberMAX, float showwidth, float showheight)
{
	ShowNumberNode *pobSprite = new ShowNumberNode();
	if (pobSprite)
	{
		pobSprite->Init(path, numberMAX, showwidth, showheight);
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

bool ShowNumberNode::Init(const char* path, int numberMAX, float showwidth, float showheight) {
	
	//��ʼ������
	this->s_NumberMax = numberMAX;
	this->s_ShowWidth = showwidth;
	this->s_ShowHeight = showheight;
	//�������ֳ���
	s_NumberLength = f_NumberLength(numberMAX);
	batchNode = CCSpriteBatchNode::create(path);
	//��numbersprite��ӽ��ڵ�
	f_addSprite();
	return true;

}

void ShowNumberNode::f_addSprite() {
	for (int i = 0; i < s_NumberLength; i++)
	{
		NumberSprite *nsp = NumberSprite::CreateNumberSprite(batchNode->getTexture(), s_ShowWidth, s_ShowHeight);
		nsp->setPosition(ccp(-s_ShowWidth * i, 0));

		batchNode->addChild(nsp, 0, i);
	}
	this->addChild(batchNode);
}

//�޸���ʾ����
void ShowNumberNode::f_ShowNumber(int number)
{
	if (number<0 || number>s_NumberMax)
		return;
	int numlength = f_NumberLength(number);
	for (int i = 0; i < s_NumberLength; i++)
	{
		int num = f_GetNumber(number, i + 1);
		NumberSprite *nsp = (NumberSprite*)batchNode->getChildByTag(i);
		//����������λ���Ĳ�������
		if (i >= numlength)
		{
			nsp->setVisible(false);
		}
		else
		{
			nsp->setVisible(true);
			nsp->f_ShowNumber(num);
		}
	}
}
//�ж��������ֵ�λ��
int ShowNumberNode::f_NumberLength(int number)
{
	if (number == 0)
		return 1;
	int flag = 0;
	while (number)
	{
		number /= 10;
		flag++;
	}
	return flag;
}
//����num���ұ߿�ʼ��kλ���ֵ�ֵ
int ShowNumberNode::f_GetNumber(int num, int k)
{
	while (k > 1)
	{
		num = num / 10;
		k--;
	}
	return num % 10;
}
ShowNumberNode::ShowNumberNode()
{
}


ShowNumberNode::~ShowNumberNode()
{
}
