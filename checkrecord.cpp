#include "checkrecord.h"
CheckRecord::CheckRecord():Window("盘点记录界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{

}

int CheckRecord::Init()
{
	this->CheckTable->AddTh("盘点编号");
	this->CheckTable->AddTh("盘点状态");
	this->CheckTable->AddTh("冲正说明");
	this->CheckTable->SetFile(new CheckNoteFile());
	this->CheckTable->SetPaging(3);
    this->CheckTable->SetClickMode(1);
	

	this->CheckTable->SetHint("盘点信息表,按Enter可进入查看详细信息");

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
	if (USER_TYPE == "盘点员") 
	{
		vector<string> Res = this->CheckTable->GetClickTd();
		CHECK_INFO_RECORD_SINGLE = *(Res.begin()) + ".txt";
		return WIN_CHECK_RECORD_SINGLE;
	}
	else if (USER_TYPE == "管理员")
	{
		vector<string> Res = this->CheckTable->GetClickTd();
		CHECK_INFO_RECORD_SINGLE = *(Res.begin()) + ".txt";
		if (*(Res.begin() + 1) != "已冲正")
		{
			CheckNoteFile* CNF = new CheckNoteFile();
			CNF->Modify(1, CHECK_INFO_RECORD_SINGLE.substr(0, 12), 2, "冲正中");
			/*设置表格重读*/
			this->CheckTable->SetLoadAgain();
		}
		return WIN_CHECK_RECORD_SINGLE;
	}
}


