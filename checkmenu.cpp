#include "checkmenu.h"

CheckMenu::CheckMenu():Window("盘点员主界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int CheckMenu::Init()
{
	this->GoodsQuery->SetHint("查询商品的编号、名称、类型、价格、数量和仓位编号");
	this->CheckStock->SetHint("盘点仓库中商品的数量");
	this->CheckRecord->SetHint("查看盘点记录，并根据需要进行复盘");
	this->Add(this->GoodsQuery);
	this->Add(this->CheckStock);
	this->Add(this->CheckRecord);
	return 0;
}

int CheckMenu::Exit()
{
	/*清除用户登录信息*/
	USER_TYPE = "请先登录!";
	USER_NAME = "请先登录!";
	USER_ID = "NULL!";
	return 0;
}

int CheckMenu::Event(Widget* Obj)
{
	if (Obj == this->GoodsQuery)
	{
		return GoodsQueryButtonEvent();
	}
	else if (Obj == this->CheckStock)
	{
		return CheckStockButtonEvent();
	}
	else if (Obj == this->CheckRecord)
	{
		return CheckRecordButtonEvent();
	}
	return WIN_NO_OPS;
}



int CheckMenu::GoodsQueryButtonEvent()
{
	return WIN_GOODS_QUERY;
}

int CheckMenu::CheckStockButtonEvent()
{
	return WIN_CHECK_STOCK;
}

int CheckMenu::CheckRecordButtonEvent()
{
	return WIN_CHECK_RECORD;
}
