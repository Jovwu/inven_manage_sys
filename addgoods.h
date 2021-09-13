#ifndef _ADD_GOODS_H_
#define _ADD_GOODS_H_
#include "window.h"
#include "label.h"
#include "edit.h"
#include "button.h"
#include "select.h"
#include "goodsfile.h"
#include "hintwin.h"
#include "goods.h"

#define ADD_GOODS_CONTINUE 11
#define ADD_GOODS_CANCEL 12

#define IMPORT_SUCCESS 11
#define IMPORT_DEFEAT 12

class AddGoods :public Window
{
public:


	AddGoods();
	int Init();//��ʼ��
	int Event(Widget* Obj);

	int AddGoodsBtnEvent();
	int ImportGoodsButtonEvent();


private:

	/*��Ʒ���(�̶�)*/
	Label* GoodsID = new Label("��Ʒ���:", 45, 10);
	Label* GoodsIDValue = new Label("NULL", 55, 10);

	/*��Ʒ��Ϣ��д*/

	Label* GoodsName = new Label("��Ʒ����:", 45, 12);
	Edit* GoodsNameEdit = new Edit(55, 12, "ONLYCHINESE", GOODS_NAME_MAX);

	Label* GoodsType = new Label("��Ʒ����:", 45, 14);
	Edit* GoodsTypeEdit = new Edit(55, 14, "ONLYCHINESE", GOODS_NAME_MAX);

	Label* GoodsPrice = new Label("��Ʒ�۸�:", 45, 16);
	Edit* GoodsPriceIntEdit = new Edit(55, 16, "ONLYFIGURE", GOODS_PRICE_INTEGER_MAX);
	Label* GoodsPriceCenter = new Label(".", 62, 16);
	Edit* GoodsPriceDecEdit = new Edit(64, 16, "ONLYFIGURE", GOODS_PRICE_DECIMALS_MAX);

	Label* GoodsCount = new Label("��Ʒ����:", 45, 18);
	Edit* GoodsCountEdit = new Edit(55, 18, "ONLYFIGURE", GOODS_COUNT_MAX);

	Label* GoodsLocID = new Label("�ֿ��ַ:", 45, 20);
	Select* GoodsLocIDSelect = new Select(56, 20);
	
	Button* AddGoodsBtn = new Button("���", 48, 23);
	Button* ImportGoods = new Button("������Ʒ", 57, 23);

};

class SameGoodsChoiceBox :public Window
{
public:

	SameGoodsChoiceBox();
	int Init();
	int Event(Widget* Obj);

private:

	Label* Msg = new Label("������ͬ���Ƶ���Ʒ���Ƿ����?", 5, 5);
	Button* AddGoods = new Button("����", 8, 11);
	Button* Cancel = new Button("����", 28, 11);

};


class ImportGoodsBox :public Window
{
public:

	ImportGoodsBox();
	int Init();
	int Event(Widget* Obj);

	int OKButtonEvent();

private:

	Label* FilePath = new Label("�ļ�·��:", 3, 6);
	Edit* FilePathEdit = new Edit(13, 6, "UNLIMITED", CHECKNOTE_EXPLAIN_MAX);
	Button* OK = new Button("ȷ��", 8, 11);
	Button* NO = new Button("����", 28, 11);
};

#endif // !_ADD_GOODS_H_
