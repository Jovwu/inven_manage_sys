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

	Label* GoodsID = new Label("��Ʒ���:", 38, 10);
	Edit* GoodsIDEdit = new Edit(49, 10, "NOTCHINESE", GOODS_ID_MAX);
	Button* Query = new Button("��ȷ��ѯ[1]",67,10);
	Button* QueryFuzzy = new Button("ģ����ѯ[2]", 82, 10);
	Table* GoodsInfo = new Table("��Ʒ��Ϣ��",20,12);

	Button* Export = new Button("�����������[3]", 52, 24);
};


class ChoiceBox :public Window
{
public:

	ChoiceBox();
	int Init();
	int Event(Widget* Obj);

private:

	Label* Msg = new Label("���޴���Ʒ���Ƿ���ӣ�", 5, 5);
	Button* AddGoods = new Button("���", 8, 11);
	Button* Cancel = new Button("ȡ��", 28, 11);

};



#endif // !_GOODS_QUERY_H_

