#include "checkrecord.h"
CheckRecord::CheckRecord():Window("�̵��¼����", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{

}

int CheckRecord::Init()
{
	this->CheckTable->AddTh("�̵���");
	this->CheckTable->AddTh("�̵�״̬");
	this->CheckTable->AddTh("����˵��");
	this->CheckTable->SetFile(new CheckNoteFile());
	this->CheckTable->SetPaging(3);
    this->CheckTable->SetClickMode(1);
	

	this->CheckTable->SetHint("�̵���Ϣ��,��Enter�ɽ���鿴��ϸ��Ϣ");

	this->Add(this->CheckTable);


	return 0;
}

int CheckRecord::Event(Widget* Obj)
{
	if (Obj == this->CheckTable) 
	{
		return CheckTableEvent();
	}
	return 0;
}

int CheckRecord::CheckTableEvent()
{
	if (USER_TYPE == "�̵�Ա") 
	{
		vector<string> Res = this->CheckTable->GetClickTd();
		CHECK_INFO_RECORD_SINGLE = *(Res.begin()) + ".txt";
		return WIN_CHECK_RECORD_SINGLE;
	}
	else if (USER_TYPE == "����Ա")
	{
		vector<string> Res = this->CheckTable->GetClickTd();
		CHECK_INFO_RECORD_SINGLE = *(Res.begin()) + ".txt";
		if (*(Res.begin() + 1) != "�ѳ���")
		{
			CheckNoteFile* CNF = new CheckNoteFile();
			CNF->Modify(1, CHECK_INFO_RECORD_SINGLE.substr(0, 12), 2, "������");
			/*���ñ���ض�*/
			this->CheckTable->SetLoadAgain();
		}
		return WIN_CHECK_RECORD_SINGLE;
	}
}


