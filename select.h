#ifndef _SELECT_H_
#define _SELECT_H_
#include "widget.h"
#include "console.h"
#include "keyboard.h"
#include <vector> 
#include <stdarg.h>
#include <cstdarg>
#include <conio.h>
class Select:public Widget
{
public:

	Select(int POSITION_X, int POSITION_Y);
	
	int Load();//控件加载-->显示到屏幕上
	int GetCursor();//获得焦点
	int LostCursor();//失去焦点
	int OnClick();//控件根据操作获得响应
	int Refresh();

	int AddOption(const string Option);

private:

	vector<string> Option;


};



#endif // 
