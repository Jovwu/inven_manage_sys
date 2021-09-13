#ifndef _GOODS_QUERY_H_
#define _GOODS_QUERY_H_
#include "window.h"
#include "table.h"
#include "button.h"
#include "label.h"
#include "edit.h"
#include "goodsfile.h"
#include "hintwin.h"

#define CHOICE_ADD 11
#define CHOICE_CANCEL 12

class GoodsQuery:public Window
{
public:

	GoodsQuery();
	int Init();
	int Event(Widget* Obj);
	
	int QueryButtonEvent();
	int QueryFuzzyButtonEvent();
	int ExportButtonEvent();

private:

	Label* GoodsID = new Label("商品编号:", 38, 10);
	Edit* GoodsIDEdit = new Edit(49, 10, "NOTCHINESE", GOODS_ID_MAX);
	Button* Query = new Button("精确查询[1]",67,10);
	Button* QueryFuzzy = new Button("模糊查询[2]", 82, 10);
	Table* GoodsInfo = new Table("商品信息表",20,12);

	Button* Export = new Button("导出表格内容[3]", 52, 24);
};


class ChoiceBox :public Window
{
public:

	ChoiceBox();
	int Init();
	int Event(Widget* Obj);

private:

	Label* Msg = new Label("查无此商品，是否添加？", 5, 5);
	Button* AddGoods = new Button("添加", 8, 11);
	Button* Cancel = new Button("取消", 28, 11);

};



#endif // !_GOODS_QUERY_H_

