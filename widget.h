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

	//子类继承时需重写方法-->通用方法
	virtual int Load() = 0;//控件加载-->显示到屏幕上
	virtual int GetCursor()  = 0;//获得焦点
	virtual int LostCursor() = 0;//失去焦点
	virtual int OnClick() = 0;//控件根据操作获得响应
	virtual int Refresh() = 0;//刷新控件

	int GetPOSITION_X() const;
	int GetPOSITION_Y() const;
	string GetValue() const;
	string GetType() const;//获得控件类型
	string GetHint() const;

	int SetPOSITION_X(int POSITION_X);
	int SetPOSITION_Y(int POSITION_Y);
	int SetValue(string Value);
	int SetType(const string Type);//设置控件类型
	int SetHint(const string HINT);


private:

	//int ID;//控件的ID
	int POSITION_X;//控件X轴位置
	int POSITION_Y;//控件Y轴位置
	string Value;//控件内容
	string TYPE;//控件类型
	string HINT;//控件选中提示

};

#endif // !_WIDGET_H_
