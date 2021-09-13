#ifndef _GOODS_IN_RECORD_H_
#define _GOODS_IN_RECORD_H_
#include "window.h"
#include "button.h"
#include "label.h"
#include "hintwin.h"
#include "table.h"
#include "edit.h"
#include "goodsoutfile.h"
class GoodsInRecord :public Window
{
public:

	GoodsInRecord();
	int Init();//��ʼ��
	int Event(Widget* Obj);
	int QueryButtonEvent();

private:


	Table* GoodsOutInfo = new Table("��Ʒ��Ϣ��", 28, 9);

	Edit* YearEdit = new Edit(38, 22, "NOTCHINESE", 4);
	Label* Year = new Label("��", 44, 22);

	Edit* MonthEdit = new Edit(47, 22, "NOTCHINESE", 2);
	Label* Month = new Label("��", 51, 22);

	Edit* DayEdit = new Edit(54, 22, "NOTCHINESE", 2);
	Label* Day = new Label("��", 58, 22);
	Button* Query = new Button("��ʱ���ѯ", 69, 22);



};



#endif // !_GOODS_IN_RECORD_H_
