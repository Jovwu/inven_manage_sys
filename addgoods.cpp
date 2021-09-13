#include "addgoods.h"

AddGoods::AddGoods() :Window("商品添加界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int AddGoods::Init()
{

	GoodsFile* GF = new GoodsFile();
	vector<string> Res = GF->SelectAllFuzzy(1, DateToString());
	if (Res.empty())
	{
		this->GoodsIDValue->SetValue(DateToString() + "0001");
	}
	else
	{
		string Str = to_string(stoi(GF->GetGoods(Res.back())->GetID().substr(8)) + 1);
		for (int Loop = Str.size(); Loop < 4; Loop++)
		{
			Str = "0" + Str;
		}
		this->GoodsIDValue->SetValue(DateToString()  + Str);

	}
	delete GF;

	this->GoodsLocIDSelect->SetHint("请选择仓位编号");
	this->GoodsLocIDSelect->AddOption("A1223");
	this->GoodsLocIDSelect->AddOption("A1224");
	this->GoodsLocIDSelect->AddOption("A4344");
	this->GoodsLocIDSelect->AddOption("B7999");

	this->GoodsNameEdit->SetHint("请输入商品名称");
	this->GoodsTypeEdit->SetHint("请输入商品类型");
	this->GoodsPriceIntEdit->SetHint("请输入商品价格,默认为0");
	this->GoodsPriceDecEdit->SetHint("请输入商品价格,默认为0");
	this->GoodsCountEdit->SetHint("请输入商品数量");
	this->GoodsLocIDSelect->SetHint("请选择仓位编号");
	this->AddGoodsBtn->SetHint("添加商品");
	this->ImportGoods->SetHint("从外部文件导入商品");

	this->Add(this->GoodsID);
	this->Add(this->GoodsIDValue);
	this->Add(this->GoodsName);
	this->Add(this->GoodsNameEdit);
	this->Add(this->GoodsType);
	this->Add(this->GoodsTypeEdit);
	this->Add(this->GoodsPrice);
	this->Add(this->GoodsPriceIntEdit);
	this->Add(this->GoodsPriceCenter);
	this->Add(this->GoodsPriceDecEdit);
	this->Add(this->GoodsCount);
	this->Add(this->GoodsCountEdit);
	this->Add(this->GoodsLocID);
	this->Add(this->GoodsLocIDSelect);
	this->Add(this->AddGoodsBtn);
	this->Add(this->ImportGoods);

	return 0;
}

int AddGoods::Event(Widget* Obj)
{
	if (Obj == this->AddGoodsBtn) 
	{
		return AddGoodsBtnEvent();
	}
	else if (Obj == this->ImportGoods)
	{
		return this->ImportGoodsButtonEvent();
	}
	return 0;
}

int AddGoods::AddGoodsBtnEvent()
{
	if(this->GoodsNameEdit->GetValue().empty()) 
	{
		(new HintWin("请输入商品名称!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->GoodsTypeEdit->GetValue().empty())
	{
		(new HintWin("请输入商品类型!"))->Run();
		return WIN_CUR_POS_2;
	}
	else if (this->GoodsPriceIntEdit->GetValue().empty() && this->GoodsPriceDecEdit->GetValue().empty())
	{
		(new HintWin("请输入商品价格!"))->Run();
		return WIN_CUR_POS_3;
	}
	else if (this->GoodsCountEdit->GetValue().empty())
	{
		(new HintWin("请输入商品数量!"))->Run();
		return WIN_CUR_POS_5;
	}
	else 
	{
		GoodsFile* GF = new GoodsFile();
		/*如果有相同名字的商品，询问*/
		if (!GF->Select(2,this->GoodsNameEdit->GetValue()).empty())
		{
			int Ret = (new SameGoodsChoiceBox())->Run();
			if (Ret == ADD_GOODS_CONTINUE)
			{
				
			}
			else if (Ret == ADD_GOODS_CANCEL) 
			{
				return WIN_REFRESH;
			}
			else 
			{
				return WIN_REFRESH;
			}
		}
		string GoodsPrice;
		if (this->GoodsPriceIntEdit->GetValue().empty())
		{
			GoodsPrice = "0";
		}
		else
		{
			GoodsPrice = this->GoodsPriceIntEdit->GetValue();
		}
		if (this->GoodsPriceDecEdit->GetValue().empty())
		{
			GoodsPrice = GoodsPrice + ".00";
		}
		else 
		{
			GoodsPrice = GoodsPrice + "." + this->GoodsPriceDecEdit->GetValue();
		}
		Goods* goods = new Goods(
			this->GoodsIDValue->GetValue(),
			this->GoodsNameEdit->GetValue(),
			this->GoodsTypeEdit->GetValue(),
			stod(GoodsPrice),
			stoi(this->GoodsCountEdit->GetValue()),
			this->GoodsLocIDSelect->GetValue()
			);
		GF->AppendGoods(goods);
		/*更新数据*/
		vector<string> Res = GF->SelectAllFuzzy(1, DateToString());
		if (Res.empty())
		{
			this->GoodsIDValue->SetValue(DateToString() + "0001");
		}
		else
		{
			string Str = to_string(stoi(GF->GetGoods(Res.back())->GetID().substr(8)) + 1);
			for (int Loop = Str.size(); Loop < 4; Loop++)
			{
				Str = "0" + Str;
			}
			this->GoodsIDValue->SetValue(DateToString() + Str);

		}
		delete GF;
		/*清空*/
		this->GoodsNameEdit->SetValue("");
		this->GoodsTypeEdit->SetValue("");
		this->GoodsPriceIntEdit->SetValue("");
		this->GoodsPriceDecEdit->SetValue("");
		this->GoodsCountEdit->SetValue("");
		(new HintWin("添加成功!"))->Run();
		return WIN_CUR_POS_1;
	}
	return WIN_REFRESH;
}

int AddGoods::ImportGoodsButtonEvent()
{
	(new ImportGoodsBox())->Run();
	return WIN_REFRESH;
}


SameGoodsChoiceBox::SameGoodsChoiceBox() :Window("提示", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int SameGoodsChoiceBox::Init()
{
	this->Add(this->Msg);
	this->Add(this->AddGoods);
	this->Add(this->Cancel);
	return 0;
}

int SameGoodsChoiceBox::Event(Widget* Obj)
{
	if (Obj == this->AddGoods)
	{
		return ADD_GOODS_CONTINUE;
	}
	else if (Obj == this->Cancel)
	{
		return ADD_GOODS_CANCEL;
	}
	return 0;
}

ImportGoodsBox::ImportGoodsBox() :Window("商品导入", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int ImportGoodsBox::Init()
{
	this->Add(this->FilePath);
	this->Add(this->FilePathEdit);
	this->Add(this->OK);
	this->Add(this->NO);
	return 0;
}

int ImportGoodsBox::Event(Widget* Obj)
{
	if (Obj == this->OK)
	{
		return OKButtonEvent();
	}
	else if (Obj == this->NO) 
	{
		return IMPORT_DEFEAT;
	}
	return 0;
}

int ImportGoodsBox::OKButtonEvent()
{
	File* file = new File(this->FilePathEdit->GetValue());
	/*导入成功*/
	if (file->CopyTo(GOODS_RECORD))
	{
		(new HintWin("导入成功!"))->Run();
		return IMPORT_SUCCESS;
	}
	else 
	{
		(new HintWin("导入失败!"))->Run();
		return IMPORT_DEFEAT;
	}
	return WIN_REFRESH;
}
