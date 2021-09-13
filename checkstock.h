#ifndef _CHECK_STOCK_H_
#define _CHECK_STOCK_H_
#include "window.h"
#include "table.h"
#include "button.h"
#include "label.h"
#include "edit.h"
#include "goodsfile.h"
#include "hintwin.h"
#include "checknotefile.h"
#include "checkinfo.h"
#include "checkinfofile.h"
#include "border.h"
#include <string>


#define CHECK_ADD 11
#define CHECK_MODIFY 12
#define CHECK_CANCEL 13

#define EXIT_CANCEL 11

#define CREATE_OK_NEW 11
#define CREATE_OK_RECORD 12
#define CREATE_NO 13

using namespace std;
class CheckStock :public Window
{
public:

	CheckStock();
	int Init();
	int Exit();
	int Event(Widget* Obj);

	int QueryButtonEvent();
	int ConfirmButtonEvent();
	int CreatCheckInfoButtonEvent();

private:

	string GoodsIDValue;

	/*�̵���*/
	Label* CheckNoteID = new Label("�̵���:", 46, 6);
	Label* CheckNoteIDValue = new Label("NULL", 56, 6);

	Label* GoodsID = new Label("��������Ʒ���:", 15, 10);
	Edit* GoodsIDEdit = new Edit(31, 10, "NOTCHINESE", GOODS_ID_MAX);
	Button* Query = new Button("��ѯ", 49, 10);

	/*��Ʒ��Ϣ*/
	Border* GoodsBorder = new Border(12, 8, 46, 15);

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

	Label* CheckCount = new Label("�������̵�������(1-10000):", 68, 14);
	Edit* CheckCountEdit = new Edit(97, 14, "NOTCHINESE", GOODS_COUNT_MAX);
	Button* Confirm = new Button("ȷ��", 75, 18);
	Button* CreatCheckInfo = new Button("�����̵��", 89, 18);


};


class CtrBox :public Window 
{
public:

	CtrBox();
	int Init();
	int Event(Widget* Obj);

private:

	Label* Msg = new Label("����Ʒ�����̵��¼����ѡ��:", 5,5);
	Button* AddCount = new Button("�ۼ�", 8, 11);
	Button* Modify = new Button("�޸�", 18, 11);
	Button* Cancel = new Button("ȡ��", 28, 11);

};



class ExitBox :public Window
{
public:

	ExitBox();
	int Init();
	int Event(Widget* Obj);


private:

	Label* Msg = new Label("����δ������̵��¼���Ƿ�����˳���", 3, 5);
	Button* OK = new Button("�����˳�", 8, 11);
	Button* NO = new Button("�ֻ���", 25, 11);

};


class CreatBox :public Window
{
public:

	CreatBox();
	int Init();
	int Event(Widget* Obj);


private:

	Label* Msg = new Label("���ɺ��޷�������̵��¼��ȷ����", 3, 5);
	Button* OKToNew = new Button("ȷ�����Ҽ����½���¼", 8, 7);
	Button* OKToRecord = new Button("ȷ�����Ҳ鿴�˴μ�¼", 8, 10);
	Button* NO = new Button("�ֻ���", 8, 13);

};
#endif // !_CHECK_STOCK_H_
