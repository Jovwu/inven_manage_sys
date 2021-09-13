#include "goodsinrecord.h"
GoodsInRecord::GoodsInRecord() :Window("��Ʒ����¼����", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int GoodsInRecord::Init()
{
	this->GoodsOutInfo->SetFile(new GoodsOutFile());
	this->GoodsOutInfo->SetPaging(3);
	this->GoodsOutInfo->SetClickMode(0);

	this->GoodsOutInfo->AddTh("��Ʒ���");
	this->GoodsOutInfo->AddTh("��Ʒ����");
	this->GoodsOutInfo->AddTh("��������");
	this->GoodsOutInfo->AddTh("��������");
	this->GoodsOutInfo->AddTh("��λ���");

	this->YearEdit->SetHint("���������");
	this->MonthEdit->SetHint("�������·�");
	this->DayEdit->SetHint("��������");
	this->Query->SetHint("��ʱ���ѯ");
	this->GoodsOutInfo->SetHint("��Ʒ����¼");

	this->Add(this->GoodsOutInfo);
	this->Add(this->YearEdit);
	this->Add(this->Year);
	this->Add(this->MonthEdit);
	this->Add(this->Month);
	this->Add(this->DayEdit);
	this->Add(this->Day);
	this->Add(this->Query);
	

	return 0;
}

int GoodsInRecord::Event(Widget* Obj)
{
	if (Obj == this->Query)
	{
		return QueryButtonEvent();
	}
	return 0;
}

int GoodsInRecord::QueryButtonEvent()
{
	if (this->YearEdit->GetValue().empty())
	{
		(new HintWin("��ݲ���Ϊ��!"))->Run();
		return WIN_CUR_POS_2;
	}
	else if (this->MonthEdit->GetValue().empty())
	{
		(new HintWin("�·ݲ���Ϊ��!"))->Run();
		return WIN_CUR_POS_3;
	}
	else if (this->DayEdit->GetValue().empty())
	{
		(new HintWin("���ڲ���Ϊ��!"))->Run();
		return WIN_CUR_POS_4;
	}
	else if (this->YearEdit->GetValue().find('0', 0) == 0
		|| this->YearEdit->GetValue().size() != 4
		|| stoi(this->MonthEdit->GetValue()) == 0
		|| stoi(this->DayEdit->GetValue()) == 0
		|| stoi(this->MonthEdit->GetValue()) > 12
		|| stoi(this->DayEdit->GetValue()) > 31)
	{
		this->YearEdit->SetValue("");
		this->MonthEdit->SetValue("");
		this->DayEdit->SetValue("");
		(new HintWin("��Ч����!"))->Run();
		return WIN_CUR_POS_2;
	}
	else
	{
		/*��ʽ������*/
		string Date;
		Date.append(this->YearEdit->GetValue());
		Date.append(this->MonthEdit->GetValue().size() == 2 ? this->MonthEdit->GetValue() : "0" + this->MonthEdit->GetValue());
		Date.append(this->DayEdit->GetValue().size() == 2 ? this->DayEdit->GetValue() : "0" + this->DayEdit->GetValue());
		/*����*/
		if (this->GoodsOutInfo->SelectAllFuzzy(3, Date) == false)
		{
			/*�������ʱ����Ϣ*/
			this->YearEdit->SetValue("");
			this->MonthEdit->SetValue("");
			this->DayEdit->SetValue("");
			(new HintWin("�����޽��!"))->Run();
			return WIN_CUR_POS_2;
		}
		this->YearEdit->SetValue("");
		this->MonthEdit->SetValue("");
		this->DayEdit->SetValue("");
		return WIN_CUR_POS_1;
	}
	return 0;
}
