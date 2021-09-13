#include "goodsinrecord.h"
GoodsInRecord::GoodsInRecord() :Window("商品入库记录界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int GoodsInRecord::Init()
{
	this->GoodsOutInfo->SetFile(new GoodsOutFile());
	this->GoodsOutInfo->SetPaging(3);
	this->GoodsOutInfo->SetClickMode(0);

	this->GoodsOutInfo->AddTh("商品编号");
	this->GoodsOutInfo->AddTh("商品名称");
	this->GoodsOutInfo->AddTh("出库日期");
	this->GoodsOutInfo->AddTh("出库数量");
	this->GoodsOutInfo->AddTh("仓位编号");

	this->YearEdit->SetHint("请输入年份");
	this->MonthEdit->SetHint("请输入月份");
	this->DayEdit->SetHint("请输入天");
	this->Query->SetHint("按时间查询");
	this->GoodsOutInfo->SetHint("商品入库记录");

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
		(new HintWin("年份不得为空!"))->Run();
		return WIN_CUR_POS_2;
	}
	else if (this->MonthEdit->GetValue().empty())
	{
		(new HintWin("月份不得为空!"))->Run();
		return WIN_CUR_POS_3;
	}
	else if (this->DayEdit->GetValue().empty())
	{
		(new HintWin("日期不得为空!"))->Run();
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
		(new HintWin("无效输入!"))->Run();
		return WIN_CUR_POS_2;
	}
	else
	{
		/*格式化日期*/
		string Date;
		Date.append(this->YearEdit->GetValue());
		Date.append(this->MonthEdit->GetValue().size() == 2 ? this->MonthEdit->GetValue() : "0" + this->MonthEdit->GetValue());
		Date.append(this->DayEdit->GetValue().size() == 2 ? this->DayEdit->GetValue() : "0" + this->DayEdit->GetValue());
		/*搜索*/
		if (this->GoodsOutInfo->SelectAllFuzzy(3, Date) == false)
		{
			/*清空所有时间信息*/
			this->YearEdit->SetValue("");
			this->MonthEdit->SetValue("");
			this->DayEdit->SetValue("");
			(new HintWin("搜索无结果!"))->Run();
			return WIN_CUR_POS_2;
		}
		this->YearEdit->SetValue("");
		this->MonthEdit->SetValue("");
		this->DayEdit->SetValue("");
		return WIN_CUR_POS_1;
	}
	return 0;
}
