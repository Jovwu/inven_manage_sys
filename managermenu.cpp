#include "managermenu.h"


ManagerMenu::ManagerMenu() :Window("管理员主界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int ManagerMenu::Init()
{
	this->GoodsQuery->SetHint("进入商品查询界面");
	this->AddGoods->SetHint("添加新的商品");
	this->GoodsInOut->SetHint("商品的出入库管理");
	this->GoodsInRecord->SetHint("查看商品入库记录");
	this->GoodsOutRecord->SetHint("查看商品出库记录");
	this->CheckRecord->SetHint("查看盘点记录,并选择冲正或者导出记录");

	this->Add(this->GoodsQuery);
	this->Add(this->AddGoods);
	this->Add(this->GoodsInOut);
	this->Add(this->GoodsOutRecord);
	this->Add(this->GoodsInRecord);
	this->Add(this->CheckRecord);

	return 0;
}

int ManagerMenu::Exit()
{
	/*清除用户登录信息*/
	USER_TYPE = "请先登录!";
	USER_NAME = "请先登录!";
	USER_ID = "NULL!";
	return 0;
}

int ManagerMenu::Event(Widget* Obj)
{
	if (Obj == this->GoodsQuery)
	{
		return WIN_GOODS_QUERY;
	}
	else if (Obj == this->AddGoods) 
	{
		return WIN_ADD_GOODS;
	}
	else if (Obj == this->GoodsInOut)
	{
		return WIN_GOODS_OUT_IN;
	}
	else if (Obj == this->GoodsOutRecord)
	{
		return WIN_GOODS_OUT_RECORD;
	}
	else if (Obj == this->GoodsInRecord)
	{
		return WIN_GOODS_IN_RECORD;
	}
	else if (Obj ==this->CheckRecord)
	{
		CheckNoteFile* CNF = new CheckNoteFile();
		CNF->Sort();
		delete CNF;
		return WIN_CHECK_RECORD;
	}
	return 0;
}
