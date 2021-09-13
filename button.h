#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <iostream>
#include "widget.h"
#include "console.h"
#include "keyboard.h"
class Window;
class Button :public Widget
{
public:

	Button(const string Value, int POSITION_X, int POSITION_Y);

	int Load();//�ؼ�����-->��ʾ����Ļ��
	int GetCursor();//��ý���
	int LostCursor();//ʧȥ����
	int OnClick();//�ؼ����ݲ��������Ӧ
	int Refresh();

private:

};



#endif // !_WIDGET_BUTTON_H_

