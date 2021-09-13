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

	/*盘点编号*/
	Label* CheckNoteID = new Label("盘点编号:", 46, 6);
	Label* CheckNoteIDValue = new Label("NULL", 56, 6);

	Label* GoodsID = new Label("请输入商品编号:", 15, 10);
	Edit* GoodsIDEdit = new Edit(31, 10, "NOTCHINESE", GOODS_ID_MAX);
	Button* Query = new Button("查询", 49, 10);

	/*商品信息*/
	Border* GoodsBorder = new Border(12, 8, 46, 15);

	Label* GoodsName = new Label("商品名称:", 20, 13);
	Label* GoodsNameValue = new Label("NULL", 31, 13);

	Label* GoodsType = new Label("商品类型:", 20, 15);
	Label* GoodsTypeValue = new Label("NULL", 31, 15);

	Label* GoodsPrice = new Label("商品价格:", 20, 17);
	Label* GoodsPriceValue = new Label("NULL", 31, 17);

	Label* GoodsCount = new Label("商品数量:", 20, 19);
	Label* GoodsCountValue = new Label("NULL", 31, 19);

	Label* GoodsLocID = new Label("仓位编号:", 20, 21);
	Label* GoodsLocIDValue = new Label("NULL", 31, 21);

	/*盘点区域*/

	Label* CheckCount = new Label("请输入盘点库存数量(1-10000):", 68, 14);
	Edit* CheckCountEdit = new Edit(97, 14, "NOTCHINESE", GOODS_COUNT_MAX);
	Button* Confirm = new Button("确定", 75, 18);
	Button* CreatCheckInfo = new Button("生成盘点表", 89, 18);


};


class CtrBox :public Window 
{
public:

	CtrBox();
	int Init();
	int Event(Widget* Obj);

private:

	Label* Msg = new Label("此商品已有盘点记录，请选择:", 5,5);
	Button* AddCount = new Button("累加", 8, 11);
	Button* Modify = new Button("修改", 18, 11);
	Button* Cancel = new Button("取消", 28, 11);

};



class ExitBox :public Window
{
public:

	ExitBox();
	int Init();
	int Event(Widget* Obj);


private:

	Label* Msg = new Label("还有未保存的盘点记录，是否继续退出？", 3, 5);
	Button* OK = new Button("继续退出", 8, 11);
	Button* NO = new Button("手滑了", 25, 11);

};


class CreatBox :public Window
{
public:

	CreatBox();
	int Init();
	int Event(Widget* Obj);


private:

	Label* Msg = new Label("生成后无法再添加盘点记录，确定？", 3, 5);
	Button* OKToNew = new Button("确定并且继续新建记录", 8, 7);
	Button* OKToRecord = new Button("确定并且查看此次记录", 8, 10);
	Button* NO = new Button("手滑了", 8, 13);

};
#endif // !_CHECK_STOCK_H_
