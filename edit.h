#ifndef _EDIT_H_
#define _EDIT_H_

#include "widget.h"
#include "keyboard.h"
#include "console.h"



class Edit :public Widget
{
public:

	Edit(int POSITION_X, int POSITION_Y, const string TEXTTYPE,int Length);

	int Load();//�ؼ�����-->��ʾ����Ļ��
	int GetCursor();//��ý���
	int LostCursor();//ʧȥ����
	int OnClick();//�ؼ����ݲ��������Ӧ

	int OnlyChinese();//ֻ����������
	int NotChinese();//�ų�����
	int OnlyFigure();//��������,����Ϊ���ֵ�λ��
	int PassWord();//����
	int Unlimited();//������
	int Refresh();

private:

	//�ɷ�༭
	string TEXTTYPE;//�ı�����
	int Length;//�ı�����


};



#endif // !_EDIT_H_
