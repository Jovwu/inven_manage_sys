#ifndef _CHECK_RECORD_SINGLE_H_
#define _CHECK_RECORD_SINGLE_H_
#include "window.h"
#include "button.h"
#include "label.h"
#include "table.h"
#include "edit.h"
#include "checkinfofile.h"
#include "hintwin.h"
#include "checknotefile.h"
#include "goodsfile.h"

#define CHECK_AGAIN_OK 11
#define CHECK_AGAIN_NO 12

#define REVERSE_OK 11
#define REVERSE_NO 12


class CheckRecordSingle :public Window
{
public:

	CheckRecordSingle();
	int Init();//初始化
	int Event(Widget* Obj);

	int TabelEvent();
	int ReverseButtonEvent();

private:

	Label* CheckNoteID = new Label("盘点编号:", 24, 8);
	Label* CheckNoteIDValue = new Label("NULL", 34, 8);
	Label* CheckState = new Label("盘点状态:", 68, 8);
	Label* CheckStateValue = new Label("NULL", 78, 8);
	Table* CheckInfo = new Table("商品信息表", 20, 11);

	Button* Reverse = new Button("冲正", 56, 24);

};

class CheckAgainBox :public Window
{
public:

	CheckAgainBox();
	int Init();
	int Event(Widget* Obj);

	bool SetGoodsID(string GoodsID);
	


private:

	string GoodsID;

	Label* CheckAgain = new Label("请输入复盘数量:", 3, 6);
	Edit* CheckAgainEdit = new Edit(19, 6, "ONLYFIGURE", CHECKINFO_CHECKCOUNT_MAX);

	Button* OK = new Button("复盘", 8, 12);
	Button* NO = new Button("取消", 24, 12);

};

class ReverseBox :public Window
{
public:

	ReverseBox();
	int Init();
	int Event(Widget* Obj);

	int OKButtonEvent();

private:

	Label* Explain = new Label("冲正说明:", 3, 6);
	Edit* ExplainEdit = new Edit(13, 6, "ONLYCHINESE", CHECKNOTE_EXPLAIN_MAX);
	Button* OK = new Button("确定", 8, 11);
	Button* NO = new Button("算了", 24, 11);
};

#endif // !_CHECK_RECORD_SINGLE_H_
