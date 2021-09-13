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

	int Load();//控件加载-->显示到屏幕上
	int GetCursor();//获得焦点
	int LostCursor();//失去焦点
	int OnClick();//控件根据操作获得响应
	int Refresh();

private:

	int Width;
	int Height;

};

#endif // !_WIDGET_LABEL_H_
