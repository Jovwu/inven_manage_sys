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

	int Load();//控件加载-->显示到屏幕上
	int GetCursor();//获得焦点
	int LostCursor();//失去焦点
	int OnClick();//控件根据操作获得响应
	int Refresh();

private:

};



#endif // !_WIDGET_BUTTON_H_

