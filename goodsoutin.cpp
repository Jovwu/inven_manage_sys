#include "goodsoutin.h"


GoodsOutIn::GoodsOutIn() :Window("商品出入库界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int GoodsOutIn::Init()
{
	this->GoodsIDEdit->SetHint("请输入商品编号");
	this->Query->SetHint("查询商品");
	this->CheckCountEdit->SetHint("请输入数量");
	this->Out->SetHint("商品出库");
	this->In->SetHint("商品入库");

	this->Add(this->GoodsID);
	this->Add(this->GoodsIDEdit);
	this->Add(this->Query);
	this->Add(this->GoodsBorder);
	this->Add(this->GoodsName);
	this->Add(this->GoodsNameValue);
	this->Add(this->GoodsType);
	this->Add(this->GoodsTypeValue);
	this->Add(this->GoodsPrice);
	this->Add(this->GoodsPriceValue);
	this->Add(this->GoodsCount);
	this->Add(this->GoodsCountValue);
	this->Add(this->GoodsLocID);
	this->Add(this->GoodsLocIDValue);
	this->Add(this->CheckCount);
	this->Add(this->CheckCountEdit);
	this->Add(this->Out);
	this->Add(this->In);

	return 0;
}

int GoodsOutIn::Event(Widget* Obj)
{
	if (Obj == this->Out) 
	{
		return OutButtonEvent();
	}
	else if (Obj == this->In) 
	{
		return InButtonEvent();
	}
	else if (Obj == this->Query) 
	{
		return QueryButtonEvent();
	}
	return 0;
}

int GoodsOutIn::QueryButtonEvent()
{
	if (this->GoodsIDEdit->GetValue().empty())
	{
		return (new HintWin("请输入商品编号!"))->Run();
	}
	else
	{
		GoodsFile* GF = new GoodsFile();
		string GoodsStr = GF->Select(1, this->GoodsIDEdit->GetValue());
		if (GoodsStr.empty())
		{
			this->GoodsIDValue.assign("");
			this->GoodsNameValue->SetValue("NULL");
			this->GoodsTypeValue->SetValue("NULL");
			this->GoodsPriceValue->SetValue("NULL");
			this->GoodsCountValue->SetValue("NULL");
			this->GoodsLocIDValue->SetValue("NULL");
			this->GoodsIDEdit->SetValue("");
			(new HintWin("查无此商品!"))->Run();
			return WIN_CUR_POS_1;
		}
		else
		{
			Goods* goods = GF->GetGoods(GoodsStr);
			this->GoodsIDValue.assign(goods->GetID());
			this->GoodsNameValue->SetValue(goods->GetName());
			this->GoodsTypeValue->SetValue(goods->GetType());
			this->GoodsPriceValue->SetValue(to_string(goods->GetPrice()));
			this->GoodsCountValue->SetValue(to_string(goods->GetCount()));
			this->GoodsLocIDValue->SetValue(goods->GetLocID());
			return WIN_CUR_POS_3;
		}
	}
	return WIN_REFRESH;
}

int GoodsOutIn::OutButtonEvent()
{
	if (this->GoodsIDValue.empty())
	{
		(new HintWin("请先进行查询!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->CheckCountEdit->GetValue().empty()) 
	{
		(new HintWin("请先输入数量!"))->Run();
		return WIN_CUR_POS_3;
	}
	else if (this->CheckCountEdit->GetValue().find('0', 0) == 0)
	{
		this->CheckCountEdit->SetValue("");
		(new HintWin("无效输入！"))->Run();
		return WIN_CUR_POS_3;
	}
	else 
	{
		/*如果此商品有未冲正或者冲正中状态下的记录，禁止出库入库*/
		/*先获取未冲正和冲正中的盘点记录*/
		CheckNoteFile* CNF = new CheckNoteFile();
		vector<string> CheckInfoID = CNF->SelectAllSingleInvert(2, "已冲正", 1);
		if (!CheckInfoID.empty())
		{
			vector<string>::iterator IDIt = CheckInfoID.begin();
			CheckInfoFile* CIF = new CheckInfoFile();
			while (IDIt != CheckInfoID.end())
			{
				CIF->SetPath(CHECK_INFO_RECORD + *IDIt + ".txt");
				/*如果找到记录*/
				if (!CIF->Select(2, this->GoodsIDValue).empty())
				{
					(new HintWin("有未冲正的盘点记录！"))->Run();
					this->GoodsIDEdit->SetValue("");
					this->CheckCountEdit->SetValue("");
					return WIN_CUR_POS_1;
				}
				IDIt++;
			}
		}else if (stoi(this->GoodsCountValue->GetValue()) < stoi(this->CheckCountEdit->GetValue()))
		{
			(new HintWin("库存不足!"))->Run();
			this->CheckCountEdit->SetValue("");
			return WIN_CUR_POS_3;
		}
		/*先添加出库记录*/
		GoodsOut* GO = new GoodsOut(
			this->GoodsIDValue,
			this->GoodsNameValue->GetValue(),
			DateToString(),
			stoi(this->CheckCountEdit->GetValue()),
			this->GoodsLocIDValue->GetValue()
		);
		GoodsOutFile* GOF = new GoodsOutFile();
		GOF->AppendGoodsOut(GO);
		/*修改商品信息*/
		GoodsFile* GF = new GoodsFile();
		GF->Modify(1,this->GoodsIDValue,5,to_string(stoi(this->GoodsCountValue->GetValue()) - stoi(this->CheckCountEdit->GetValue())));
		/*刷新页面值*/
		string GoodsStr = GF->Select(1, this->GoodsIDEdit->GetValue());
		Goods* goods = GF->GetGoods(GoodsStr);
		this->GoodsCountValue->SetValue(to_string(goods->GetCount()));
		this->CheckCountEdit->SetValue("");
		(new HintWin("出库成功！"))->Run();
		return WIN_CUR_POS_3;
	}
	return WIN_REFRESH;
}

int GoodsOutIn::InButtonEvent()
{
	if (this->GoodsIDValue.empty())
	{
		(new HintWin("请先进行查询!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->CheckCountEdit->GetValue().empty())
	{
		(new HintWin("请先输入数量!"))->Run();
		return WIN_CUR_POS_3;
	}
	else if (this->CheckCountEdit->GetValue().find('0',0) == 0)
	{
		this->CheckCountEdit->SetValue("");
		(new HintWin("无效输入！"))->Run();
		return WIN_CUR_POS_3;
	}
	else
	{
		/*如果此商品有未冲正或者冲正中状态下的记录，禁止出库入库*/
		/*先获取未冲正和冲正中的盘点记录*/
		CheckNoteFile* CNF = new CheckNoteFile();
		vector<string> CheckInfoID = CNF->SelectAllSingleInvert(2, "已冲正", 1);
		if (!CheckInfoID.empty())
		{
			vector<string>::iterator IDIt = CheckInfoID.begin();
			CheckInfoFile* CIF = new CheckInfoFile();
			while (IDIt != CheckInfoID.end())
			{
				CIF->SetPath(CHECK_INFO_RECORD + *IDIt + ".txt");
				/*如果找到记录*/
				if (!CIF->Select(2, this->GoodsIDValue).empty())
				{
					(new HintWin("有未冲正的盘点记录！"))->Run();
					this->GoodsIDEdit->SetValue("");
					this->CheckCountEdit->SetValue("");
					return WIN_CUR_POS_1;
				}
				IDIt++;
			}
		}
		/*先添加入库记录*/
		GoodsIn* GI = new GoodsIn(
			this->GoodsIDValue,
			this->GoodsNameValue->GetValue(),
			DateToString(),
			stoi(this->CheckCountEdit->GetValue()),
			this->GoodsLocIDValue->GetValue()
		);
		GoodsInFile* GIF = new GoodsInFile();
		GIF->AppendGoodsIn(GI);
		/*修改商品信息*/
		GoodsFile* GF = new GoodsFile();
		GF->Modify(1, this->GoodsIDValue, 5, to_string(stoi(this->GoodsCountValue->GetValue()) + stoi(this->CheckCountEdit->GetValue())));
		/*刷新页面值*/
		string GoodsStr = GF->Select(1, this->GoodsIDEdit->GetValue());
		Goods* goods = GF->GetGoods(GoodsStr);
		this->GoodsCountValue->SetValue(to_string(goods->GetCount()));
		this->CheckCountEdit->SetValue("");
		(new HintWin("入库成功！"))->Run();
		return WIN_CUR_POS_3;
	}
	return WIN_REFRESH;
}
