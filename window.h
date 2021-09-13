#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <vector>
#include <stack>
#include "widget.h"
#include "console.h"
#include "config.h"
#include "time.h"
#include "file.h"
using namespace std;

class Window
{
public:

	Window(const string Title,int PositionX, int PositionY,int Width,int Height,const string Type);

	virtual int Init() = 0;//初始化
	virtual int Event(Widget* Obj) = 0;//控件事件
	virtual int Exit();//页面退出
	int Add(Widget* widget);//控件添加
	int Load();//页面加载
	int Run();//运行
	int Refresh();//刷新界面
	int ShowHint(const string Hint);//显示控件提示信息
	
protected:

	//基本信息
	int Width;//宽度
	int Height;//高度
	int PositionX;//左上角X
	int PositionY;//左上角Y
	string Type;//窗口类型
	//显示信息
	string Title;//标题
    //控件
	vector<Widget*> WidgetVec;
	stack<Window*> MsgBoxSt;
	//自动消失标志位-->用于提示框
	int VanishFlag;

};



#endif // !_WINDOW_H_
