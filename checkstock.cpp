#include "checkstock.h"
#pragma once

CheckStock::CheckStock():Window("新建盘点界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{


}
int CheckStock::Init()
{
	/*清空文件*/
	CheckInfoFile* CIF = new CheckInfoFile();
	CIF->ClearFile();
	/*设置盘点编号*/
	CheckNoteFile* CNF = new CheckNoteFile();
	vector<string> Res = CNF->SelectAllFuzzy(1, DateToString());
	if (Res.empty())
	{
		this->CheckNoteIDValue->SetValue(DateToString() + "-" + "001");
	}
	else
	{   
		string Str = to_string(stoi(CNF->GetCheckNote(Res.back())->GetID().substr(9)) + 1);
		for (int Loop = Str.size(); Loop < 3; Loop ++)
		{
			Str = "0" + Str;
		}
		this->CheckNoteIDValue->SetValue(DateToString() + "-" + Str);
		
	}
	delete CNF;


	this->GoodsIDEdit->SetHint("请输入商品编号");
	this->Query->SetHint("查询商品详细信息");
	this->CheckCountEdit->SetHint("请输入您要盘点的库存数量，数量限制在1~10000之间");
	this->Confirm->SetHint("确定盘点后将生成盘点数量,若想追加盘点,请不要生成盘点表");
	this->CreatCheckInfo->SetHint("生成盘点表后可查看所有盘点记录,并根据情况进行复盘");


	this->Add(this->CheckNoteID);
	this->Add(this->CheckNoteIDValue);
	this->Add(this->GoodsID);
	this->Add(this->GoodsIDEdit);
	this->Add(this->Query);
	this->Add(GoodsBorder);
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
	this->Add(this->Confirm);
	this->Add(this->CreatCheckInfo);

	return 0;
}

int CheckStock::Exit()
{
	CheckInfoFile* CIF = new CheckInfoFile();
	/*如果未保存盘点记录*/
	if (CIF->Count() != 0)
	{
		if ((new ExitBox())->Run() == WIN_EXIT)
		{
			/*确认退出*/
			/*清空文件*/
			CIF->ClearFile();
			delete CIF;
			return WIN_NO_OPS;
		}
		else 
		{
			return WIN_REFRESH;
		}
	}
	/*已保存或者没有记录*/
	return WIN_NO_OPS;
}


int CheckStock::Event(Widget* Obj)
{
	if (Obj == this->Query) 
	{
		return this->QueryButtonEvent();
	}
	else if(Obj == this->Confirm)
	{
		return this->ConfirmButtonEvent();
	}
	else if (Obj == this->CreatCheckInfo)
	{
		return this->CreatCheckInfoButtonEvent();
	}
	return 0;
}

int CheckStock::QueryButtonEvent()
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
			delete goods;
			this->GoodsIDEdit->SetValue("");
			return WIN_CUR_POS_3;
		}
		
	}
	return WIN_REFRESH;
}

int CheckStock::ConfirmButtonEvent()
{
	if (this->GoodsNameValue->GetValue() == "NULL")
	{
		(new HintWin("请先进行商品查询!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->CheckCountEdit->GetValue().empty())
	{
		(new HintWin("请输入盘点数量!"))->Run();
		return WIN_CUR_POS_3;
	}
	else
	{
		CheckInfoFile* CIF = new CheckInfoFile();
		/*新增盘点*/
		if (CIF->Select(2,this->GoodsIDValue).empty())
		{
			CheckInfo* checkinfo = new CheckInfo(
			USER_ID,
				this->GoodsIDValue,
				stoi(this->GoodsCountValue->GetValue()),
				stoi(this->CheckCountEdit->GetValue())
				);
			CIF->AppendCheckInfo(checkinfo);
			delete CIF;
			this->CheckCountEdit->SetValue("");
			(new HintWin("盘点成功!"))->Run();
			return WIN_CUR_POS_1;
		}
		/*追加盘点*/
		else
		{
			int Res = (new CtrBox())->Run();
			if (Res == CHECK_ADD)
			{
				/*先取出原来的盘点数量相加*/
				int CheckCountOrg = stoi(CIF->SelectSingle(2,this->GoodsIDValue,4));
				/*修改盘点数量和差异数量*/
				int CheckCountNew = CheckCountOrg + stoi(this->CheckCountEdit->GetValue());
				CIF->Modify(2, this->GoodsIDValue,4, to_string(CheckCountNew));
				CIF->Modify(2, this->GoodsIDValue, 5, to_string(abs(stoi(this->GoodsCountValue->GetValue()) - CheckCountNew)));
				this->CheckCountEdit->SetValue("");
				(new HintWin("累加成功!"))->Run();
				return WIN_CUR_POS_1;
			}
			else if (Res == CHECK_MODIFY) 
			{
				/*取出原来的商品数量*/
				/*修改盘点数量和差异数量*/
				CIF->Modify(2, this->GoodsIDValue, 4, this->CheckCountEdit->GetValue());
				CIF->Modify(2, this->GoodsIDValue, 5, to_string(abs(stoi(this->GoodsCountValue->GetValue()) - stoi(this->CheckCountEdit->GetValue()))));
				this->CheckCountEdit->SetValue("");
				(new HintWin("修改成功!"))->Run();
				return WIN_CUR_POS_1;
			}
			else if (Res == CHECK_CANCEL) 
			{
				this->CheckCountEdit->SetValue("");
				return WIN_CUR_POS_1;
			}
			return WIN_REFRESH;
		}
		/*创建一条盘点信息，先放进checkinfo，但是如果不点击生成盘点表的话，将清除所有盘点信息*/
		/*如果盘点记录里有盘点信息的话，但是没有生成盘点表，退出该界面时需要提示*/
		/*追加盘点提示*/
	}
	return WIN_NO_OPS;
}

int CheckStock::CreatCheckInfoButtonEvent()
{
	CheckInfoFile* CIF = new CheckInfoFile();
	/*如果没有盘点记录*/
	if (CIF->Count() == 0)
	{
		(new HintWin("没有盘点记录！"))->Run();
		this->GoodsIDEdit->SetValue("");
		this->CheckCountEdit->SetValue("");
		return WIN_CUR_POS_1;
	}
	else 
	{
		/*确认提示*/
		int Ret = (new CreatBox())->Run();
		if (Ret == CREATE_OK_NEW)
		{
			/*先创建文件*/
			CIF->CopyTo(CHECK_INFO_RECORD + this->CheckNoteIDValue->GetValue() + ".txt");
			/*写入CheckNote*/
			CheckNoteFile* CNF = new CheckNoteFile();
			CNF->AppendCheckNote(new CheckNote(this->CheckNoteIDValue->GetValue()));
			(new HintWin("生成成功！"))->Run();
			/*刷新界面的值*/
			/*重新刷新盘点编号*/
			vector<string> Res = CNF->SelectAllFuzzy(1, DateToString());
			if (Res.empty())
			{
				this->CheckNoteIDValue->SetValue(DateToString() + "-" + "001");
			}
			else
			{
				string Str = to_string(stoi(CNF->GetCheckNote(Res.back())->GetID().substr(9)) + 1);
				for (int Loop = Str.size(); Loop < 3; Loop++)
				{
					Str = "0" + Str;
				}
				this->CheckNoteIDValue->SetValue(DateToString() + "-" + Str);
			}
			/*刷新界面的属性值*/
			this->GoodsIDValue = "";
			this->GoodsIDEdit->SetValue("");
			this->GoodsNameValue->SetValue("NULL");
			this->GoodsTypeValue->SetValue("NULL");
			this->GoodsPriceValue->SetValue("NULL");
			this->GoodsCountValue->SetValue("NULL");
			this->GoodsLocIDValue->SetValue("NULL");
			this->CheckCountEdit->SetValue("");
			/*清空checkInfo*/
			CIF->ClearFile();
			delete CNF;
			delete CIF;
			return WIN_CUR_POS_1;
		}
		else if (Ret == CREATE_OK_RECORD)
		{   
			/*先创建文件*/
			CIF->CopyTo(CHECK_INFO_RECORD + this->CheckNoteIDValue->GetValue() + ".txt");
			/*写入CheckNote*/
			CheckNoteFile* CNF = new CheckNoteFile();
			CNF->AppendCheckNote(new CheckNote(this->CheckNoteIDValue->GetValue()));
			CHECK_INFO_RECORD_SINGLE = this->CheckNoteIDValue->GetValue() + ".txt";
			/*刷新界面的值*/
			/*重新刷新盘点编号*/
			vector<string> Res = CNF->SelectAllFuzzy(1, DateToString());
			if (Res.empty())
			{
				this->CheckNoteIDValue->SetValue(DateToString() + "-" + "001");
			}
			else
			{
				string Str = to_string(stoi(CNF->GetCheckNote(Res.back())->GetID().substr(9)) + 1);
				for (int Loop = Str.size(); Loop < 3; Loop++)
				{
					Str = "0" + Str;
				}
				this->CheckNoteIDValue->SetValue(DateToString() + "-" + Str);
			}
			/*刷新界面的属性值*/
			this->GoodsIDValue = "";
			this->GoodsIDEdit->SetValue("");
			this->GoodsNameValue->SetValue("NULL");
			this->GoodsTypeValue->SetValue("NULL");
			this->GoodsPriceValue->SetValue("NULL");
			this->GoodsCountValue->SetValue("NULL");
			this->GoodsLocIDValue->SetValue("NULL");
			this->CheckCountEdit->SetValue("");
			CIF->ClearFile();
			delete CNF;
			delete CIF;
			return WIN_CHECK_RECORD_SINGLE;
		}
		else if(Ret == CREATE_NO)
		{
			return WIN_CUR_POS_1;
		}
		else if (Ret == WIN_REFRESH)
		{
			return WIN_REFRESH;
        }
	}
	return 0;
}

/**********************************************************************************************/

CtrBox::CtrBox():Window("提示", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int CtrBox::Init()
{
	this->Add(this->Msg);
	this->Add(this->AddCount);
	this->Add(this->Modify);
	this->Add(this->Cancel);
	return 0;
}

int CtrBox::Event(Widget* Obj)
{
	if (Obj == this->AddCount)
	{
		return CHECK_ADD;
	}
	else if (Obj == this->Modify) 
	{
		return CHECK_MODIFY;
	}
	else if (Obj == this->Cancel)
	{
		return CHECK_CANCEL;
	}
}

/**********************************************************************************************/
ExitBox::ExitBox() :Window("提示", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int ExitBox::Init()
{
	this->Add(this->Msg);
	this->Add(this->OK);
	this->Add(this->NO);
	return 0;
}

int ExitBox::Event(Widget* Obj)
{
	if (Obj == this->OK)
	{
		CheckInfoFile* CIF = new CheckInfoFile();
		CIF->ClearFile();
		return WIN_EXIT;
	}
	else if (Obj == this->NO)
	{
		/*空操作*//*需修改*/
		return EXIT_CANCEL;
	}
	return 0;
	
}
/**********************************************************************************************/

CreatBox::CreatBox() :Window("提示", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int CreatBox::Init()
{
	this->Add(this->Msg);
	this->Add(this->OKToNew);
	this->Add(this->OKToRecord);
	this->Add(this->NO);
	return 0;
}

int CreatBox::Event(Widget* Obj)
{
	if (Obj == this->OKToNew)
	{
		return CREATE_OK_NEW;
	}
	else if (Obj == this->OKToRecord)
	{
		/*空操作*//*需修改*/
		return CREATE_OK_RECORD;
	}
	else if (Obj == this->NO)
	{
		return CREATE_NO;
	}
	return 0;
}
