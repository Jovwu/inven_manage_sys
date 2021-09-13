#include "checkrecordsingle.h"
CheckRecordSingle::CheckRecordSingle() :Window("盘点信息界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int CheckRecordSingle::Init()
{
	this->CheckInfo->SetFile(new CheckInfoFile(CHECK_INFO_RECORD_SINGLE));
	this->CheckInfo->SetPaging(3);
	if (USER_TYPE == "盘点员")
	{
		this->CheckInfo->SetClickMode(1);
	}

	this->CheckInfo->AddTh("盘点员");
	this->CheckInfo->AddTh("商品编号");
	this->CheckInfo->AddTh("初始数量");
	this->CheckInfo->AddTh("盘点数量");
	this->CheckInfo->AddTh("差异数量");
	this->CheckInfo->AddTh("复盘状态");

	this->CheckInfo->SetHint("盘点详情表");
	this->Reverse->SetHint("对盘点记录进行冲正处理");

	this->CheckNoteIDValue->SetValue(CHECK_INFO_RECORD_SINGLE.substr(0,12));
	CheckNoteFile* CNF = new CheckNoteFile();
	this->CheckStateValue->SetValue(CNF->SelectSingle(1,this->CheckNoteIDValue->GetValue(),2));

	this->Add(this->CheckNoteID);
	this->Add(this->CheckNoteIDValue);
	this->Add(this->CheckState);
	this->Add(this->CheckStateValue);
	this->Add(this->CheckInfo);

	/*管理员*/
	if (USER_TYPE == "管理员") 
	{
		/*如果已冲正，显示导出按钮*/
		if (CNF->SelectSingle(1, this->CheckNoteIDValue->GetValue(),2) == "已冲正")
		{
			this->Reverse->SetHint("导出盘点记录到外部文件");
			this->Reverse->SetValue("导出盘点");
		}
		this->Add(this->Reverse);
	}
	return 0;
}

int CheckRecordSingle::Event(Widget* Obj)
{
	if (Obj == this->CheckInfo)
	{
		return TabelEvent();
	}
	else if (Obj == this->Reverse) 
	{
		return this->ReverseButtonEvent();
	}
	return 0;
}

int CheckRecordSingle::TabelEvent()
{
	/*盘点员*/
	if (USER_TYPE == "盘点员") 
	{
		if (this->CheckStateValue->GetValue() != "未冲正")
		{
			return (new HintWin(this->CheckStateValue->GetValue() + "时无法操作!"))->Run();
		}
		/*取出记录*/
		vector<string> Res = this->CheckInfo->GetClickTd();
		/*如果是已复盘*/
		if (*(Res.begin() + 5) == "已复盘")
		{
			return (new HintWin("该记录已复盘!"))->Run();
		}
		/*如果是未复盘*/
		else
		{
			CheckAgainBox* CAB = new CheckAgainBox();
			CAB->SetGoodsID(*(Res.begin() + 1));
			int Res = CAB->Run();
			if (Res == CHECK_AGAIN_OK)
			{
			}
			else if (Res == CHECK_AGAIN_NO)
			{
			}
			return WIN_REFRESH;
		}
		return WIN_REFRESH;
	}
}

int CheckRecordSingle::ReverseButtonEvent()
{
	/*导出盘点功能*/
	if (this->Reverse->GetValue() == "导出盘点")
	{
		(new HintWin("正在导出..."))->Run();
		this->CheckInfo->ExprotContent(EXPORT_FILE_PATH + CHECK_INFO_RECORD_SINGLE + "CI");
		return (new HintWin("导出成功"))->Run();
	}
	else if (this->Reverse->GetValue() == "冲正")
	{
		/*若已冲正*/
		if (this->CheckStateValue->GetValue() == "已冲正")
		{
			this->Reverse->SetHint("导出盘点记录到外部文件");
			this->Reverse->SetValue("导出盘点");
			return (new HintWin("该记录已冲正!"))->Run();
		}
		/*还未冲正*/
		int Ret = (new ReverseBox())->Run();
		if (Ret == REVERSE_OK)
		{
			/*修改页面标记*/
			this->CheckStateValue->SetValue("已冲正");
			/*根据文件修改商品数量*/
			/*获得盘点文件里的所有商品*/
			CheckInfoFile* CIF = new CheckInfoFile(CHECK_INFO_RECORD_SINGLE);
			GoodsFile* GF = new GoodsFile();
			vector<string> GoodsCheck = CIF->All();
			vector<string>::iterator It = GoodsCheck.begin();
			vector<string> Res;
			while (It != GoodsCheck.end())
			{
				Res = Split(*It);
				/*获得该商品ID*/
				/*获得该商品盘点数量*/
				/*修改*/
				GF->Modify(1, *(Res.begin() + 1), 5, *(Res.begin() + 3));
				It++;
			}
			/*对文件重新排序*/
			CheckNoteFile* CNF = new CheckNoteFile();
			CNF->Sort();
			delete CNF;
			this->Reverse->SetHint("导出盘点记录到外部文件");
			this->Reverse->SetValue("导出盘点");
			return WIN_REFRESH;
		}
		else if (Ret == REVERSE_NO)
		{
			return WIN_REFRESH;
		}
	}
	
	return WIN_REFRESH;
}

/***********************************************************************************/
CheckAgainBox::CheckAgainBox() :Window("复盘界面", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int CheckAgainBox::Init()
{
	this->Add(this->CheckAgain);
	this->Add(this->CheckAgainEdit);
	this->Add(this->OK);
	this->Add(this->NO);
	return 0;
}

int CheckAgainBox::Event(Widget* Obj)
{
	if (Obj == this->OK) 
	{
		if (!this->CheckAgainEdit->GetValue().empty()) 
		{
			CheckInfoFile* CIF = new CheckInfoFile(CHECK_INFO_RECORD_SINGLE);
			/*修改盘点数量*/
			CIF->Modify(2,this->GoodsID,4, this->CheckAgainEdit->GetValue());
			/*修改差异数量*/
			CIF->Modify(2, this->GoodsID, 5, 
				to_string(abs(stoi(CIF->SelectSingle(2, this->GoodsID,3))-stoi(this->CheckAgainEdit->GetValue()))));
			/*修改复盘状态*/
			CIF->Modify(2, this->GoodsID, 6, "已复盘");
			(new HintWin("复盘成功!"))->Run();
			return CHECK_AGAIN_OK;
		}
	}
	else if(Obj == this->NO) 
	{
		return CHECK_AGAIN_NO;
	}
	return 0;
}

bool CheckAgainBox::SetGoodsID(string GoodsID)
{
	this->GoodsID.assign(GoodsID);
	return true;
}

/*************************************************************************************************/

ReverseBox::ReverseBox() :Window("冲正界面", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int ReverseBox::Init()
{
	this->Add(this->Explain);
	this->Add(this->ExplainEdit);
	this->Add(this->OK);
	this->Add(this->NO);
	return 0;
}

int ReverseBox::Event(Widget* Obj)
{
	if (Obj == this->OK) 
	{
		return OKButtonEvent();
	}
	else if (Obj == this->NO)
	{
		return REVERSE_NO;
	}
	return 0;
}

int ReverseBox::OKButtonEvent()
{
	/*修改冲正状态*/
	CheckNoteFile* CNF = new CheckNoteFile();
	CNF->Modify(1, CHECK_INFO_RECORD_SINGLE.substr(0, 12),2,"已冲正");
	/*修改冲正说明*/
	if (!this->ExplainEdit->GetValue().empty()) 
	{
		CNF->Modify(1, CHECK_INFO_RECORD_SINGLE.substr(0, 12), 3, this->ExplainEdit->GetValue());
	}
	else 
	{
		CNF->Modify(1, CHECK_INFO_RECORD_SINGLE.substr(0, 12), 3, "无");
	}
	return REVERSE_OK;
}
