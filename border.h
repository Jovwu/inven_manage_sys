#ifndef _BORDER_H_
#define _BORDER_H_
#include <iostream>
#include "widget.h"
#include "console.h"
#include "keyboard.h"
using namespace std;
class Border :public Widget
{
public:

	Border(int POSITION_X, int POSITION_Y,int Width,int Height);

	int Load();//�ؼ�����-->��ʾ����Ļ��
	int GetCursor();//��ý���
	int LostCursor();//ʧȥ����
	int OnClick();//�ؼ����ݲ��������Ӧ
	int Refresh();

private:

	int Width;
	int Height;

};

#endif // !_WIDGET_LABEL_H_
