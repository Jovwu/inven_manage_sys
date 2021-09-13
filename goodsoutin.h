#ifndef _GOODS_OUT_IN_H_
#define _GOODS_OUT_IN_H_
#include "window.h"
#include "label.h"
#include "edit.h"
#include "button.h"
#include "hintwin.h"
#include "goods.h"
#include "goodsfile.h"
#include <string>
#include "goodsinfile.h"
#include "goodsoutfile.h"
#include "goodsin.h"
#include "goodsout.h"
#include "border.h"
#include "checknotefile.h"
#include "checkinfofile.h"
using namespace std;

class GoodsOutIn :public Window
{
public:

	GoodsOutIn();
	int Init();
	int Event(Widget* Obj);
	int QueryButtonEvent();
	int OutButtonEvent();
	int InButtonEvent();

private:

	string GoodsIDValue;
	/*�̵���*/
	Label* GoodsID = new Label("��������Ʒ���:", 15, 10);
	Edit* GoodsIDEdit = new Edit(31, 10, "NOTCHINESE", GOODS_ID_MAX);
	Button* Query = new Button("��ѯ", 49, 10);

	/*��Ʒ��Ϣ*/
	Border* GoodsBorder = new Border(12,8,46,15);

	Label* GoodsName = new Label("��Ʒ����:", 20, 13);
	Label* GoodsNameValue = new Label("NULL", 31, 13);

	Label* GoodsType = new Label("��Ʒ����:", 20, 15);
	Label* GoodsTypeValue = new Label("NULL", 31, 15);

	Label* GoodsPrice = new Label("��Ʒ�۸�:", 20, 17);
	Label* GoodsPriceValue = new Label("NULL", 31, 17);

	Label* GoodsCount = new Label("��Ʒ����:", 20, 19);
	Label* GoodsCountValue = new Label("NULL", 31, 19);

	Label* GoodsLocID = new Label("��λ���:", 20, 21);
	Label* GoodsLocIDValue = new Label("NULL", 31, 21);

	/*�̵�����*/
	Label* CheckCount = new Label("����������(1-10000):", 68, 14);
	Edit* CheckCountEdit = new Edit(90, 14, "NOTCHINESE", GOODS_COUNT_MAX);
	Button* Out = new Button("����", 75, 18);
	Button* In = new Button("���", 89, 18);

};

#endif // !_GOODS_OUT_IN_H_
