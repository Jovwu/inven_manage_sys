#include "goodsquery.h"
GoodsQuery::GoodsQuery():Window("商品查询界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{

}
int GoodsQuery::Init()
{
	this->GoodsInfo->SetFile(new GoodsFile());
	this->GoodsInfo->SetPaging(3);
	this->GoodsInfo->SetClickMode(0);

	this->GoodsInfo->AddTh("商品编号");
	this->GoodsInfo->AddTh("商品名称");
	this->GoodsInfo->AddTh("商品类型");
	this->GoodsInfo->AddTh("商品价格");
	this->GoodsInfo->AddTh("库存数量");
	this->GoodsInfo->AddTh("仓位编号");


	this->GoodsIDEdit->SetHint("请输入商品的ID");
	this->Query->SetHint("精确查询商品");
	this->QueryFuzzy->SetHint("模糊查询商品");
	this->GoodsInfo->SetHint("商品信息表");
	this->Export->SetHint("导出表格内容到外部文件");


	this->Add(this->GoodsID);
	this->Add(this->GoodsIDEdit);
	this->Add(this->Query);
	this->Add(this->QueryFuzzy);
	this->Add(this->GoodsInfo);
	this->Add(this->Export);

	return 0;
}

int GoodsQuery::Event(Widget* Obj)
{
	if (Obj == this->Query)
	{
		return QueryButtonEvent();
	}
	else if (Obj == this->QueryFuzzy)
	{
		return QueryFuzzyButtonEvent();
	}
	else if (Obj == this->Export) 
	{
		return ExportButtonEvent();
	}
	return 0;
}

int GoodsQuery::QueryButtonEvent()
{
	if (this->GoodsIDEdit->GetValue().empty()) 
	{
		(new HintWin("请输入商品编号!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->GoodsInfo->Select(1, this->GoodsIDEdit->GetValue()) == false)
	{
		if (USER_TYPE == "管理员") 
		{
			/*先询问是否需要添加新商品*/
			int Ret = (new ChoiceBox())->Run();
			if (Ret == CHOICE_ADD)
			{
				this->GoodsInfo->SetLoadAgain();
				/*到商品添加页面*/
				return WIN_ADD_GOODS;
			}
			else if (Ret == CHOICE_CANCEL)
			{
				this->GoodsIDEdit->SetValue("");
				return WIN_CUR_POS_1;
			}
			return WIN_REFRESH;
		}
		else if (USER_TYPE == "盘点员") 
		{
			(new HintWin("找不到该商品!"))->Run();
			this->GoodsIDEdit->SetValue("");
			return WIN_CUR_POS_1;
		}
	}
	/*找到后*/
	return WIN_NO_OPS;
}

int GoodsQuery::QueryFuzzyButtonEvent()
{
	if (this->GoodsIDEdit->GetValue().empty())
	{
		(new HintWin("请输入商品编号!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->GoodsInfo->SelectAllFuzzy(1, this->GoodsIDEdit->GetValue()) == false)
	{
		(new HintWin("无查询结果!"))->Run();
		this->GoodsIDEdit->SetValue("");
		return WIN_CUR_POS_1;
	}
	/*找到结果*/
	else 
	{
		return WIN_CUR_POS_4;
	}
	return 0;
}

int GoodsQuery::ExportButtonEvent()
{
	(new HintWin("正在导出..."))->Run();
	this->GoodsInfo->ExprotContent(EXPORT_FILE_PATH + DateToString() + "GI" + ".txt");
	return (new HintWin("导出成功"))->Run();
}

ChoiceBox::ChoiceBox() :Window("提示", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int ChoiceBox::Init()
{
	this->Add(this->Msg);
	this->Add(this->AddGoods);
	this->Add(this->Cancel);
	return 0;
}

int ChoiceBox::Event(Widget* Obj)
{
	if (Obj == this->AddGoods)
	{
		return CHOICE_ADD;
	}
	else if (Obj == this->Cancel)
	{
		return CHOICE_CANCEL;
	}
	return 0;
}
