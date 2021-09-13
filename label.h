#ifndef _LABEL_H_
#define _LABEL_H_

#include <iostream>
#include "widget.h"
#include "console.h"
#include "keyboard.h"

using namespace std;
class Label :public Widget
{
public:

	Label(const string Value, int POSITION_X, int POSITION_Y);

	int Load();//�ؼ�����-->��ʾ����Ļ��
	int GetCursor();//��ý���
	int LostCursor();//ʧȥ����
	int OnClick();//�ؼ����ݲ��������Ӧ
	int Refresh();


};

#endif // !_WIDGET_LABEL_H_
