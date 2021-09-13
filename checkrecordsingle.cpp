#include "checkrecordsingle.h"
CheckRecordSingle::CheckRecordSingle() :Window("�̵���Ϣ����", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int CheckRecordSingle::Init()
{
	this->CheckInfo->SetFile(new CheckInfoFile(CHECK_INFO_RECORD_SINGLE));
	this->CheckInfo->SetPaging(3);
	if (USER_TYPE == "�̵�Ա")
	{
		this->CheckInfo->SetClickMode(1);
	}

	this->CheckInfo->AddTh("�̵�Ա");
	this->CheckInfo->AddTh("��Ʒ���");
	this->CheckInfo->AddTh("��ʼ����");
	this->CheckInfo->AddTh("�̵�����");
	this->CheckInfo->AddTh("��������");
	this->CheckInfo->AddTh("����״̬");

	this->CheckInfo->SetHint("�̵������");
	this->Reverse->SetHint("���̵��¼���г�������");

	this->CheckNoteIDValue->SetValue(CHECK_INFO_RECORD_SINGLE.substr(0,12));
	CheckNoteFile* CNF = new CheckNoteFile();
	this->CheckStateValue->SetValue(CNF->SelectSingle(1,this->CheckNoteIDValue->GetValue(),2));

	this->Add(this->CheckNoteID);
	this->Add(this->CheckNoteIDValue);
	this->Add(this->CheckState);
	this->Add(this->CheckStateValue);
	this->Add(this->CheckInfo);

	/*����Ա*/
	if (USER_TYPE == "����Ա") 
	{
		/*����ѳ�������ʾ������ť*/
		if (CNF->SelectSingle(1, this->CheckNoteIDValue->GetValue(),2) == "�ѳ���")
		{
			this->Reverse->SetHint("�����̵��¼���ⲿ�ļ�");
			this->Reverse->SetValue("�����̵�");
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
	/*�̵�Ա*/
	if (USER_TYPE == "�̵�Ա") 
	{
		if (this->CheckStateValue->GetValue() != "δ����")
		{
			return (new HintWin(this->CheckStateValue->GetValue() + "ʱ�޷�����!"))->Run();
		}
		/*ȡ����¼*/
		vector<string> Res = this->CheckInfo->GetClickTd();
		/*������Ѹ���*/
		if (*(Res.begin() + 5) == "�Ѹ���")
		{
			return (new HintWin("�ü�¼�Ѹ���!"))->Run();
		}
		/*�����δ����*/
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
	/*�����̵㹦��*/
	if (this->Reverse->GetValue() == "�����̵�")
	{
		(new HintWin("���ڵ���..."))->Run();
		this->CheckInfo->ExprotContent(EXPORT_FILE_PATH + CHECK_INFO_RECORD_SINGLE + "CI");
		return (new HintWin("�����ɹ�"))->Run();
	}
	else if (this->Reverse->GetValue() == "����")
	{
		/*���ѳ���*/
		if (this->CheckStateValue->GetValue() == "�ѳ���")
		{
			this->Reverse->SetHint("�����̵��¼���ⲿ�ļ�");
			this->Reverse->SetValue("�����̵�");
			return (new HintWin("�ü�¼�ѳ���!"))->Run();
		}
		/*��δ����*/
		int Ret = (new ReverseBox())->Run();
		if (Ret == REVERSE_OK)
		{
			/*�޸�ҳ����*/
			this->CheckStateValue->SetValue("�ѳ���");
			/*�����ļ��޸���Ʒ����*/
			/*����̵��ļ����������Ʒ*/
			CheckInfoFile* CIF = new CheckInfoFile(CHECK_INFO_RECORD_SINGLE);
			GoodsFile* GF = new GoodsFile();
			vector<string> GoodsCheck = CIF->All();
			vector<string>::iterator It = GoodsCheck.begin();
			vector<string> Res;
			while (It != GoodsCheck.end())
			{
				Res = Split(*It);
				/*��ø���ƷID*/
				/*��ø���Ʒ�̵�����*/
				/*�޸�*/
				GF->Modify(1, *(Res.begin() + 1), 5, *(Res.begin() + 3));
				It++;
			}
			/*���ļ���������*/
			CheckNoteFile* CNF = new CheckNoteFile();
			CNF->Sort();
			delete CNF;
			this->Reverse->SetHint("�����̵��¼���ⲿ�ļ�");
			this->Reverse->SetValue("�����̵�");
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
CheckAgainBox::CheckAgainBox() :Window("���̽���", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
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
			/*�޸��̵�����*/
			CIF->Modify(2,this->GoodsID,4, this->CheckAgainEdit->GetValue());
			/*�޸Ĳ�������*/
			CIF->Modify(2, this->GoodsID, 5, 
				to_string(abs(stoi(CIF->SelectSingle(2, this->GoodsID,3))-stoi(this->CheckAgainEdit->GetValue()))));
			/*�޸ĸ���״̬*/
			CIF->Modify(2, this->GoodsID, 6, "�Ѹ���");
			(new HintWin("���̳ɹ�!"))->Run();
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

ReverseBox::ReverseBox() :Window("��������", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
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
	/*�޸ĳ���״̬*/
	CheckNoteFile* CNF = new CheckNoteFile();
	CNF->Modify(1, CHECK_INFO_RECORD_SINGLE.substr(0, 12),2,"�ѳ���");
	/*�޸ĳ���˵��*/
	if (!this->ExplainEdit->GetValue().empty()) 
	{
		CNF->Modify(1, CHECK_INFO_RECORD_SINGLE.substr(0, 12), 3, this->ExplainEdit->GetValue());
	}
	else 
	{
		CNF->Modify(1, CHECK_INFO_RECORD_SINGLE.substr(0, 12), 3, "��");
	}
	return REVERSE_OK;
}
