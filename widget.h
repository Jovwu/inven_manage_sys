#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <stdio.h>
#include <string>
#include <string.h>
#include "keyboard.h"
using namespace std;
class Widget
{
public:

	//Widget();
	Widget(const string Value, int POSITION_X, int POSITION_Y);

	//����̳�ʱ����д����-->ͨ�÷���
	virtual int Load() = 0;//�ؼ�����-->��ʾ����Ļ��
	virtual int GetCursor()  = 0;//��ý���
	virtual int LostCursor() = 0;//ʧȥ����
	virtual int OnClick() = 0;//�ؼ����ݲ��������Ӧ
	virtual int Refresh() = 0;//ˢ�¿ؼ�

	int GetPOSITION_X() const;
	int GetPOSITION_Y() const;
	string GetValue() const;
	string GetType() const;//��ÿؼ�����
	string GetHint() const;

	int SetPOSITION_X(int POSITION_X);
	int SetPOSITION_Y(int POSITION_Y);
	int SetValue(string Value);
	int SetType(const string Type);//���ÿؼ�����
	int SetHint(const string HINT);


private:

	//int ID;//�ؼ���ID
	int POSITION_X;//�ؼ�X��λ��
	int POSITION_Y;//�ؼ�Y��λ��
	string Value;//�ؼ�����
	string TYPE;//�ؼ�����
	string HINT;//�ؼ�ѡ����ʾ

};

#endif // !_WIDGET_H_
