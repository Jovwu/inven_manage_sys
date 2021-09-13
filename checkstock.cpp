#include "checkstock.h"
#pragma once

CheckStock::CheckStock():Window("�½��̵����", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{


}
int CheckStock::Init()
{
	/*����ļ�*/
	CheckInfoFile* CIF = new CheckInfoFile();
	CIF->ClearFile();
	/*�����̵���*/
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


	this->GoodsIDEdit->SetHint("��������Ʒ���");
	this->Query->SetHint("��ѯ��Ʒ��ϸ��Ϣ");
	this->CheckCountEdit->SetHint("��������Ҫ�̵�Ŀ������������������1~10000֮��");
	this->Confirm->SetHint("ȷ���̵�������̵�����,����׷���̵�,�벻Ҫ�����̵��");
	this->CreatCheckInfo->SetHint("�����̵���ɲ鿴�����̵��¼,������������и���");


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
	/*���δ�����̵��¼*/
	if (CIF->Count() != 0)
	{
		if ((new ExitBox())->Run() == WIN_EXIT)
		{
			/*ȷ���˳�*/
			/*����ļ�*/
			CIF->ClearFile();
			delete CIF;
			return WIN_NO_OPS;
		}
		else 
		{
			return WIN_REFRESH;
		}
	}
	/*�ѱ������û�м�¼*/
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
		return (new HintWin("��������Ʒ���!"))->Run();
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
			(new HintWin("���޴���Ʒ!"))->Run();
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
		(new HintWin("���Ƚ�����Ʒ��ѯ!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->CheckCountEdit->GetValue().empty())
	{
		(new HintWin("�������̵�����!"))->Run();
		return WIN_CUR_POS_3;
	}
	else
	{
		CheckInfoFile* CIF = new CheckInfoFile();
		/*�����̵�*/
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
			(new HintWin("�̵�ɹ�!"))->Run();
			return WIN_CUR_POS_1;
		}
		/*׷���̵�*/
		else
		{
			int Res = (new CtrBox())->Run();
			if (Res == CHECK_ADD)
			{
				/*��ȡ��ԭ�����̵��������*/
				int CheckCountOrg = stoi(CIF->SelectSingle(2,this->GoodsIDValue,4));
				/*�޸��̵������Ͳ�������*/
				int CheckCountNew = CheckCountOrg + stoi(this->CheckCountEdit->GetValue());
				CIF->Modify(2, this->GoodsIDValue,4, to_string(CheckCountNew));
				CIF->Modify(2, this->GoodsIDValue, 5, to_string(abs(stoi(this->GoodsCountValue->GetValue()) - CheckCountNew)));
				this->CheckCountEdit->SetValue("");
				(new HintWin("�ۼӳɹ�!"))->Run();
				return WIN_CUR_POS_1;
			}
			else if (Res == CHECK_MODIFY) 
			{
				/*ȡ��ԭ������Ʒ����*/
				/*�޸��̵������Ͳ�������*/
				CIF->Modify(2, this->GoodsIDValue, 4, this->CheckCountEdit->GetValue());
				CIF->Modify(2, this->GoodsIDValue, 5, to_string(abs(stoi(this->GoodsCountValue->GetValue()) - stoi(this->CheckCountEdit->GetValue()))));
				this->CheckCountEdit->SetValue("");
				(new HintWin("�޸ĳɹ�!"))->Run();
				return WIN_CUR_POS_1;
			}
			else if (Res == CHECK_CANCEL) 
			{
				this->CheckCountEdit->SetValue("");
				return WIN_CUR_POS_1;
			}
			return WIN_REFRESH;
		}
		/*����һ���̵���Ϣ���ȷŽ�checkinfo�������������������̵��Ļ�������������̵���Ϣ*/
		/*����̵��¼�����̵���Ϣ�Ļ�������û�������̵���˳��ý���ʱ��Ҫ��ʾ*/
		/*׷���̵���ʾ*/
	}
	return WIN_NO_OPS;
}

int CheckStock::CreatCheckInfoButtonEvent()
{
	CheckInfoFile* CIF = new CheckInfoFile();
	/*���û���̵��¼*/
	if (CIF->Count() == 0)
	{
		(new HintWin("û���̵��¼��"))->Run();
		this->GoodsIDEdit->SetValue("");
		this->CheckCountEdit->SetValue("");
		return WIN_CUR_POS_1;
	}
	else 
	{
		/*ȷ����ʾ*/
		int Ret = (new CreatBox())->Run();
		if (Ret == CREATE_OK_NEW)
		{
			/*�ȴ����ļ�*/
			CIF->CopyTo(CHECK_INFO_RECORD + this->CheckNoteIDValue->GetValue() + ".txt");
			/*д��CheckNote*/
			CheckNoteFile* CNF = new CheckNoteFile();
			CNF->AppendCheckNote(new CheckNote(this->CheckNoteIDValue->GetValue()));
			(new HintWin("���ɳɹ���"))->Run();
			/*ˢ�½����ֵ*/
			/*����ˢ���̵���*/
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
			/*ˢ�½��������ֵ*/
			this->GoodsIDValue = "";
			this->GoodsIDEdit->SetValue("");
			this->GoodsNameValue->SetValue("NULL");
			this->GoodsTypeValue->SetValue("NULL");
			this->GoodsPriceValue->SetValue("NULL");
			this->GoodsCountValue->SetValue("NULL");
			this->GoodsLocIDValue->SetValue("NULL");
			this->CheckCountEdit->SetValue("");
			/*���checkInfo*/
			CIF->ClearFile();
			delete CNF;
			delete CIF;
			return WIN_CUR_POS_1;
		}
		else if (Ret == CREATE_OK_RECORD)
		{   
			/*�ȴ����ļ�*/
			CIF->CopyTo(CHECK_INFO_RECORD + this->CheckNoteIDValue->GetValue() + ".txt");
			/*д��CheckNote*/
			CheckNoteFile* CNF = new CheckNoteFile();
			CNF->AppendCheckNote(new CheckNote(this->CheckNoteIDValue->GetValue()));
			CHECK_INFO_RECORD_SINGLE = this->CheckNoteIDValue->GetValue() + ".txt";
			/*ˢ�½����ֵ*/
			/*����ˢ���̵���*/
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
			/*ˢ�½��������ֵ*/
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

CtrBox::CtrBox():Window("��ʾ", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
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
ExitBox::ExitBox() :Window("��ʾ", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
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
		/*�ղ���*//*���޸�*/
		return EXIT_CANCEL;
	}
	return 0;
	
}
/**********************************************************************************************/

CreatBox::CreatBox() :Window("��ʾ", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
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
		/*�ղ���*//*���޸�*/
		return CREATE_OK_RECORD;
	}
	else if (Obj == this->NO)
	{
		return CREATE_NO;
	}
	return 0;
}
