#ifndef _EDIT_H_
#define _EDIT_H_

#include "widget.h"
#include "keyboard.h"
#include "console.h"



class Edit :public Widget
{
public:

	Edit(int POSITION_X, int POSITION_Y, const string TEXTTYPE,int Length);

	int Load();//控件加载-->显示到屏幕上
	int GetCursor();//获得焦点
	int LostCursor();//失去焦点
	int OnClick();//控件根据操作获得响应

	int OnlyChinese();//只限输入中文
	int NotChinese();//排除中文
	int OnlyFigure();//仅限数字,参数为数字的位数
	int PassWord();//密码
	int Unlimited();//无限制
	int Refresh();

private:

	//可否编辑
	string TEXTTYPE;//文本类型
	int Length;//文本长度


};



#endif // !_EDIT_H_
