#include "table.h"
Table::Table(const string Value, int POSITION_X, int POSITION_Y) :Widget(Value, POSITION_X, POSITION_Y)
{
	this->ClickMode = CLICK_NULL;
	this->CursorLine = 0;
	this->ContentFlag = INFO_ORG;
	this->LoadContentFlag = 0;
}
int Table::Load()
{
	//先获得横线相关
	int RowLine = this->Row + 3;
	int RowWidth = 0;
	vector<int>::iterator It = this->ThW.begin();
	while (It != this->ThW.end())
	{
		RowWidth += *It;
		It++;
	}
	RowWidth = RowWidth + this->Th.size() + 1;//给竖线空出位置
	//画出提示框的中心位置
	this->HintCenterX = RowWidth/2 + this->GetPOSITION_X();
	this->HintCenterY = (this->Row + 1) * 2 + 1 + this->GetPOSITION_Y();
	GoToXY(this->HintCenterX, this->HintCenterY);
	cout << "/";
	//画横线
	for (int Loop = 0;Loop < RowLine;Loop++)
	{
		GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y()+Loop*2);
		for (int Count = 0;Count< RowWidth;Count++)
		{
			cout << "-";
		}
	}
	//获得竖线相关
	this->Col = this->Th.size();
	int ColLine = Col + 1;
	int ColWidth = this->Row + 1;
	int Interval = 0;//间隔
	It = this->ThW.begin();
	//再画竖线
	
	while (It != this->ThW.end()) 
	{
		//单条竖线
		for (int Loop = 0; Loop < ColWidth; Loop++)
		{
			GoToXY(this->GetPOSITION_X() + Interval, this->GetPOSITION_Y() + Loop * 2 + 1);
			cout << "|";
		}
		Interval = *It + Interval + 1;
		It++;
	}
	//补上最后一条线
	for (int Loop = 0; Loop < ColWidth; Loop++)
	{
		GoToXY(this->GetPOSITION_X() + Interval, this->GetPOSITION_Y() +  Loop  * 2 + 1);
		cout << "|";
	}
	//补上消息框的线
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y() + (Row + 2) * 2 - 1);
	cout << "|";
	GoToXY(this->GetPOSITION_X() + Interval, this->GetPOSITION_Y() + ( Row + 2 ) * 2 - 1);
	cout << "|";
	//加载表头
	It = this->ThW.begin();
	int ThNum = 0;
	Interval = 0;
	while (It != this->ThW.end())
	{
		GoToXY(this->GetPOSITION_X() + Interval + 1, this->GetPOSITION_Y() + 1);
		cout << *(this->Th.begin() + ThNum);
		Interval = *It + Interval + 1;
		It++;
		ThNum++;
	}
	/*加载当前页数和总页数*/
	/*左边箭头提示*/
	GoToXY(this->HintCenterX - to_string(this->PageNum).size(), this->HintCenterY);
	cout << this->PageNum;
	/*右边箭头显示*/
	GoToXY(this->HintCenterX + to_string(this->TotalPageNum).size(), this->HintCenterY);
	cout << this->TotalPageNum;
	//加载表格->取第一页的数据
	Update(this->PageNum);
	return 0;
}

int Table::GetCursor()
{
	//第一行文本获得焦点
	if (this->CursorLine != 0)
	{
		ClickHint();
	}
	RefreshHint();
	return OnClick();
}

int Table::LostCursor()
{
	//清除文本焦点
	if (this->CursorLine != 0)
	{
		ClearHint();
	}
	/*删除左边箭头提示*/
	GoToXY(this->HintCenterX - to_string(this->PageNum).size() - 2, this->HintCenterY);
	cout << "  ";
	cout << this->PageNum;
	/*删除右边箭头显示*/
	GoToXY(this->HintCenterX + to_string(this->TotalPageNum).size(), this->HintCenterY);
	cout << this->TotalPageNum;
	cout << "   ";
	return 0;
}

int Table::OnClick()
{
	/*ClickMode = CLICK_NULL时*/
	if (this->ClickMode == CLICK_NULL)
	{
		int Key = 0;
		while (1)
		{
			Key = GetKey();
			if (Key == UP_KEY)//控件焦点往上移动
			{
				this->LostCursor();
				return Key;
			}
			else if (Key == DOWN_KEY)//控件焦点往下移动
			{
				this->LostCursor();
				return Key;
			}
			else if (Key == LEFT_KEY)//往左翻页
			{
				if (this->PageNum == 1)//如果在第一页，不做任何操作 
				{
					continue;
				}
				else
				{
					/*如果有焦点，清除焦点*/
					/*焦点来自搜索和手动操作*/
					if (this->CursorLine != 0)
					{
						this->ClearHint();
						this->CursorLine = 0;
					}
					this->Update(--this->PageNum);
					RefreshHint();
				}
			}
			else if (Key == RIGHT_KEY)//往右翻页
			{
				if (this->PageNum == this->TotalPageNum)//如果在最后一页，不做任何操作 
				{
					continue;
				}
				else
				{
					if (this->CursorLine != 0)
					{
						this->ClearHint();
						this->CursorLine = 0;
					}
					this->Update(++this->PageNum);
					RefreshHint();
				}
			}
			else if (Key == ENTER_KEY)
			{
				/*如果有焦点存在*/
				if (this->CursorLine != 0)
				{
					/*将该行录入到被选中的内容*/
					this->ClickTd = this->Content.at((this->PageNum-1) * this->Row + this->CursorLine)->GetContent();
					return ENTER_KEY;
				}
				else 
				{
					continue;
				}
			}
			else if (Key == ESC_KEY)
			{
				return ESC_KEY;
			}
			else if (Key == TAB_KEY) 
			{
				if (this->CursorLine != 0)
				{
					this->ClearHint();
					this->CursorLine = 0;
				}
				this->LostCursor();
				return TAB_KEY;
			}
			else if (Key > 48 && Key <= 59)
			{
				LostCursor();
				return Key;
			}
		}
	
	}
	/*ClickMode = CLICK_ENTER时*/
	else if (this->ClickMode == CLICK_ENTER)
	{
		int Key = 0;
		while (1)
		{
			Key = GetKey();
			if (Key == UP_KEY)//焦点往上移动
			{
				if (this->CursorLine == 1)//如果在第一行，退出循环
				{
					LostCursor();
					return UP_KEY;
				}
				else
				{
					ClearHint();
					this->CursorLine--;
					ClickHint();
				}
			}
			else if (Key == DOWN_KEY)//焦点往下移动
			{
				/*如果在最后一行或者在该页面的最后一条数据，退出循环*/
				if ((this->CursorLine == this->Row) || ((this->PageNum - 1) * this->Row + this->CursorLine == this->ContentTotal))
				{
					LostCursor();
					return DOWN_KEY;
				}
				else
				{
					ClearHint();
					this->CursorLine++;
					ClickHint();
				}
			}
			else if (Key == LEFT_KEY)//往左翻页
			{
				if (this->PageNum == 1)//如果在第一页，不做任何操作 
				{
					continue;
				}
				else
				{
					ClearHint();
					this->CursorLine = 1;
					this->Update(--this->PageNum);
					ClickHint();
					RefreshHint();
				}

			}
			else if (Key == RIGHT_KEY)//往右翻页
			{
				if (this->PageNum == this->TotalPageNum)//如果在最后一页，不做任何操作 
				{
					continue;
				}
				else
				{
					ClearHint();
					this->CursorLine = 1;
					this->Update(++this->PageNum);
					ClickHint();
					RefreshHint();
				}

			}
			else if (Key == ENTER_KEY)
			{
				this->ClickTd = this->Content.at((this->PageNum-1)*this->Row+this->CursorLine-1)->GetContent();
				return ENTER_KEY;
			}
			else if (Key == TAB_KEY)
			{
				LostCursor();
				return TAB_KEY;
			}
			else if (Key == ESC_KEY)
			{
				return ESC_KEY;
			}
			else if (Key > 48 && Key <= 59)
			{
				LostCursor();
				return Key;
			}
		}
	}
	return 0;
}

int Table::Refresh()
{
	//先获得横线相关
	int RowLine = this->Row + 3;
	int RowWidth = 0;
	vector<int>::iterator It = this->ThW.begin();
	while (It != this->ThW.end())
	{
		RowWidth += *It;
		It++;
	}
	RowWidth = RowWidth + this->Th.size() + 1;//给竖线空出位置
	//画出提示框的中心位置
	this->HintCenterX = RowWidth / 2 + this->GetPOSITION_X();
	this->HintCenterY = (this->Row + 1) * 2 + 1 + this->GetPOSITION_Y();
	GoToXY(this->HintCenterX, this->HintCenterY);
	cout << "/";
	//画横线
	for (int Loop = 0; Loop < RowLine; Loop++)
	{
		GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y() + Loop * 2);
		for (int Count = 0; Count < RowWidth; Count++)
		{
			cout << "-";
		}
	}
	//获得竖线相关
	this->Col = this->Th.size();
	int ColLine = Col + 1;
	int ColWidth = this->Row + 1;
	int Interval = 0;//间隔
	It = this->ThW.begin();
	//再画竖线

	while (It != this->ThW.end())
	{
		//单条竖线
		for (int Loop = 0; Loop < ColWidth; Loop++)
		{
			GoToXY(this->GetPOSITION_X() + Interval, this->GetPOSITION_Y() + Loop * 2 + 1);
			cout << "|";
		}
		Interval = *It + Interval + 1;
		It++;
	}
	//补上最后一条线
	for (int Loop = 0; Loop < ColWidth; Loop++)
	{
		GoToXY(this->GetPOSITION_X() + Interval, this->GetPOSITION_Y() + Loop * 2 + 1);
		cout << "|";
	}
	//补上消息框的线
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y() + (Row + 2) * 2 - 1);
	cout << "|";
	GoToXY(this->GetPOSITION_X() + Interval, this->GetPOSITION_Y() + (Row + 2) * 2 - 1);
	cout << "|";
	//加载表头
	It = this->ThW.begin();
	int ThNum = 0;
	Interval = 0;
	while (It != this->ThW.end())
	{
		GoToXY(this->GetPOSITION_X() + Interval + 1, this->GetPOSITION_Y() + 1);
		cout << *(this->Th.begin() + ThNum);
		Interval = *It + Interval + 1;
		It++;
		ThNum++;
	}
	if (this->CursorLine != 0) 
	{
		/*更新一下当前条的内容，从文件里面取*/
		/*获取当前条的位置*/
		int CurretContentPos = this->Content.at((this->PageNum - 1) * this->Row + this->CursorLine - 1)->GetFileNum();
		/*获得当前条在文件中的内容*/
		vector<string> Res = Split(this->file->SelectByRow(CurretContentPos));
		/*如果当前内容为搜索内容*/
		if (this->ContentFlag == INFO_SELECT)
		{
			/*先替换搜索内容*/
			vector<Td*>::iterator It = this->SelectContent.begin();
			while (It != this->SelectContent.end())
			{
				if ((*It)->GetFileNum() == CurretContentPos)
				{
					(*It)->SetContent(Res);
					break;
				}
				It++;
			}
		}
		/*替换原本内容*/
		this->Content.at(CurretContentPos - 1)->SetContent(Res);
		/*更新页面*/
	}
	/*加载当前页数和总页数*/
	/*左边箭头提示*/
	GoToXY(this->HintCenterX - to_string(this->PageNum).size(), this->HintCenterY);
	cout << this->PageNum;
	/*右边箭头显示*/
	GoToXY(this->HintCenterX + to_string(this->TotalPageNum).size(), this->HintCenterY);
	cout << this->TotalPageNum;
	/*如果有重读被激活*/
	if (this->LoadContentFlag == 1) 
	{
		this->InputAllContent();
		this->LoadContentFlag = 0;
	}
	Update(this->PageNum);
	return 0;
}

int Table::AddTh(const string ThMember)
{
	string Res = "--" + ThMember + "--";
	this->Th.push_back(Res);
	SetThW(Res.size());
	return 0;
}

int Table::SetThW(int ThW)
{
	this->ThW.push_back(ThW);
	return 0;
}

int Table::ClickHint()
{
	if (this->CursorLine == 0)
	{
		return 0;
	}else if (this->ContentTotal == 0) 
	{
		return 0;
	}
	else 
	{
		//定位到该页面指定行头
		int Interval;//文本间隔
		vector<string> Res;
		Interval = 0;
		//获取该行原本数据
		Res = this->Content.at((this->PageNum - 1) * Row + this->CursorLine - 1)->GetContent();
		Intensity();
		//写入
		for (int LoopCol = 0; LoopCol < this->Col; LoopCol++)
		{
			GoToXY(this->GetPOSITION_X() + Interval + 1, this->GetPOSITION_Y() + 3 + (this->CursorLine - 1) * 2);
			cout << *(Res.begin() + LoopCol);
			//补齐高亮显示
			for (int LoopSpace = 0; LoopSpace < this->ThW.at(LoopCol) - (*(Res.begin() + LoopCol)).size(); LoopSpace++)
			{
				cout << " ";
			}
			Interval = Interval + 1 + *(this->ThW.begin() + LoopCol);
		}
		OrgColor();
		return 0;
	}
	
	return 0;
}

int Table::ClearHint()
{
	if (this->CursorLine == 0)
	{
		return 0;
	}
	else if (this->ContentTotal == 0)
	{
		return 0;
	}
	else
	{
		//定位到该页面指定行头
		int Interval;//文本间隔
		vector<string> Res;
		Interval = 0;
		//获取该行原本数据
		Res = this->Content.at((this->PageNum - 1) * Row + this->CursorLine - 1)->GetContent();
		//写入
		for (int LoopCol = 0; LoopCol < this->Col; LoopCol++)
		{
			//先清除该区域
			ClearArea(this->GetPOSITION_X() + Interval + 1, this->GetPOSITION_Y() + 3 + (this->CursorLine - 1) * 2, *(this->ThW.begin() + LoopCol));
			GoToXY(this->GetPOSITION_X() + Interval + 1, this->GetPOSITION_Y() + 3 + (this->CursorLine - 1) * 2);
			cout << *(Res.begin() + LoopCol);
			Interval = Interval + 1 + *(this->ThW.begin() + LoopCol);
		}
		return 0;
	}
	return 0;
}

bool Table::Update(int Page)
{   /*进入该方法的前提是表格实际上有这页，不管有没有显示过*/
	if (Page <= 0 || Page > this->TotalPageNum) 
	{
		return false;
	}
	/*跨页更新(跨没有显示过的页面进行更新)*/
	/*需要先判断跨几页*/
	/*将之前没读取过的数据先读取到数组*/
	/*然后再显示*/
	/*判断是否读取过该内容*/
	/*没有读取过*/
	if (Page > this->BrowseYet)
	{
		/*先计算有多少数据需要读取*/
		int InputCount = (Page - this->BrowseYet) * this->Row;
		/*再将所有待取数据读入*/
		vector<string> Res;
		for (int Loop = 0; Loop < InputCount ; Loop ++) 
		{
			Res = Split(file->SelectByRow(this->BrowseYet * this->Row + Loop + 1 ));
			if (!Res.empty())
			{
				/*添加新数据*/
				this->Content.push_back(new Td(
					Res, 
					(this->BrowseYet * this->Row + Loop + 1) % this->Row == 0 ? this->Row : (this->BrowseYet * this->Row + Loop + 1) % this->Row,
					this->BrowseYet * this->Row + Loop + 1));//添加新数据
			}
		}
		this->BrowseYet = Page;
		
	}
	/*每次更新表格内容前先清除焦点*/
	this->ClearHint();
	/*更新表格内容*/
	vector<Td*>::iterator It = this->Content.begin() + (Page - 1) * this->Row;//获得每页头一条数据
	vector<string> Res;
	int Interval;//数据写入间隔
	int Flag = 0;//当没有数据时触发
	for (int LoopRow = 0; LoopRow < this->Row; LoopRow++)//行
	{
		Interval = 0;
		/*当该页已经没有数据*/
		if (Flag == 0 && (It + LoopRow) == this->Content.end())
		{
			Flag = 1;
		}
		//写入
		for (int LoopCol = 0; LoopCol < this->Col; LoopCol++)
		{
			ClearArea(this->GetPOSITION_X() + Interval + 1, this->GetPOSITION_Y() + 3 + LoopRow * 2, *(this->ThW.begin() + LoopCol));
			if (Flag != 1)
			{
				/*如果没有数据，清除该区域*/
				Res = (*(It + LoopRow))->GetContent();	//获得数组中的一行数据
				GoToXY(this->GetPOSITION_X() + Interval + 1, this->GetPOSITION_Y() + 3 + LoopRow * 2);
				cout << *(Res.begin() + LoopCol);
			}
			Interval = Interval + 1 + *(this->ThW.begin() + LoopCol);
		}
	}
	this->PageNum = Page;
	return true;
}

bool Table::PushState()
{
	this->StateStack.push(this->ContentTotal);
	this->StateStack.push(this->TotalPageNum);
	this->StateStack.push(this->PageNum);
	this->StateStack.push(this->BrowseYet);
	this->StateStack.push(this->CursorLine);
	/*this->StateStack.push(this->ClickMode);
	this->StateStack.push(this->SelectMode);*/
	return true;
}

bool Table::PopState()
{
	if (this->StateStack.empty())
	{
		return false;
	}
	this->CursorLine = this->StateStack.top();
	this->StateStack.pop();

	this->BrowseYet = this->StateStack.top();
	this->StateStack.pop();

	this->PageNum = this->StateStack.top();
	this->StateStack.pop();

	this->TotalPageNum = this->StateStack.top();
	this->StateStack.pop();

	this->ContentTotal = this->StateStack.top();
	this->StateStack.pop();

	return true;
}

bool Table::RefreshHint()
{
	/*左边箭头提示*/
	GoToXY(this->HintCenterX - to_string(this->PageNum).size() - 2, this->HintCenterY);
	if (this->TotalPageNum == 1) 
	{
		cout << "  ";
	}else if(this->PageNum == 1)
	{
		cout <<"≮";
	}
	else
	{
		cout << "＜";
	}
	cout << this->PageNum;
	/*右边箭头显示*/
	GoToXY(this->HintCenterX + to_string(this->TotalPageNum).size() , this->HintCenterY);
	cout << this->TotalPageNum;
	if (this->TotalPageNum == 1)
	{
		cout << "  ";
	}
	else if (this->PageNum == this->TotalPageNum)
	{
		cout << "≯";
	}
	else
	{
		cout << "＞";
	}
	return true;
}

bool Table::Select(int Parameter, const string Target)
{

	int InfoRow = this->file->SelectRow(Parameter,Target);
	/*找不到数据*/
	if (InfoRow == 0)
	{
		return false;
	}
	/*先恢复表格的状态*/
	if (this->ContentFlag == INFO_SELECT) 
	{
		this->PopState();
		/*恢复Content的内容*/
		this->Content.swap(this->SelectContent);
		this->ContentFlag = INFO_ORG;
	}
	/*先确认该数据所在的页数和行数*/
	this->PageNum = InfoRow / this->Row;
	if (InfoRow % this->Row)
	{
		this->PageNum++;
	} 
	this->CursorLine = InfoRow - (this->PageNum - 1) * this->Row;
	/*给这条数据高亮显示*/
	this->Update(this->PageNum);
	this->ClickHint();
	/*加载当前页数和总页数*/
	/*左边箭头提示*/
	GoToXY(this->HintCenterX - to_string(this->PageNum).size(), this->HintCenterY);
	cout << this->PageNum;
	/*右边箭头显示*/
	GoToXY(this->HintCenterX + to_string(this->TotalPageNum).size(), this->HintCenterY);
	cout << this->TotalPageNum;
	return true;
	
}

bool Table::SelectAllFuzzy(int Parameter, const string Target)
{
	/*界面清除*/
	this->ClearHint();
	/*如果查询没结果*/
	vector<string> Ret = this->file->SelectAllFuzzy(Parameter, Target);
	if (Ret.empty())
	{
		return false;
	}
	/*如果查询之前有进行原始内容替换，先将表格状态恢复到初始值*/
	if (this->ContentFlag == INFO_ORG)
	{
		this->PushState();
	}
	else if (this->ContentFlag == INFO_SELECT)
	{
		/*恢复Content的内容*/
		this->Content.swap(this->SelectContent);
	}
	/*先清空查找结果*/
	this->SelectContent.clear();
	/*将结果写入SelectContent*/
	vector<string>::iterator RetIt = Ret.begin();
	int FileNum = 1;
	while (RetIt != Ret.end())
	{
		this->SelectContent.push_back(new Td(Split(*RetIt), FileNum % this->Row == 0 ? this->Row: FileNum % this->Row,FileNum));
		FileNum++;
		RetIt++;
	}
	/*交换值*/
	this->Content.swap(this->SelectContent);
	/*设置一些标志位*/
	this->ContentFlag = INFO_SELECT;
	this->ContentTotal = Ret.size();
	this->TotalPageNum = this->ContentTotal % this->Row == 0 ? this->ContentTotal / this->Row : this->ContentTotal / this->Row + 1;
	this->PageNum = 1;
	this->BrowseYet = this->TotalPageNum;
	if (ClickMode == CLICK_NULL)
	{
		this->CursorLine = 0;
	}
	else if (ClickMode == CLICK_ENTER)
	{
		this->CursorLine = 1;
	}
	/*更新界面*/
	this->Update(this->PageNum);
	this->ClickHint();
	RefreshHint();
	return true;
}

bool Table::SetClickMode(int ClickMode)
{
	if (ClickMode == CLICK_NULL)
	{
		this->ClickMode = ClickMode;
		return true;
	}
	else if(ClickMode == CLICK_ENTER)
	{
		this->ClickMode = ClickMode;
		this->CursorLine = 1;
		return true;
	}
	return false;
}
int Table::SetFile(File* file)
{
	this->file = file;
	SetContentTotal(file->Count());//设置信息总条数
	return 0;
}

int Table::SetPaging(int Row)
{
	this->Row = Row;
	this->TotalPageNum = this->ContentTotal / this->Row;
	if (this->ContentTotal % this->Row)
	{
		this->TotalPageNum++;
	}
	this->PageNum = 1;
	this->BrowseYet = 0;
	return 0;
}

vector<string> Table::GetClickTd() const
{
	return this->ClickTd;
}

vector<Td*> Table::GetContent() const
{
	return this->Content;
}

bool Table::ExprotContent(const string Path)
{
	this->InputAllContent();
	/*打开文件*/
	File* file = new File(Path);
	/*写入数据*/
	vector<Td*> Content = this->GetContent();
	vector<Td*>::iterator It = Content.begin();
	while (It != Content.end())
	{
		vector<string> Res = (*It)->GetContent();
		vector<string>::iterator StrIt = Res.begin();
		string Str;
		while (StrIt != Res.end())
		{
			Str = Str + *StrIt + " ";
			StrIt++;
		}
		file->Append(Str);
		It++;
	}
	return true;
}

bool Table::InputAllContent()
{
	/*先计算有多少数据需要读取*/
	this->ContentTotal = this->file->Count();
	/*清空原来的content*/
	this->Content.clear();
	/*再将所有待取数据读入*/
	vector<string> Res;
	for (int Loop = 0; Loop < this->ContentTotal; Loop++)
	{
		Res = Split(file->SelectByRow(Loop + 1));
		if (!Res.empty())
		{
			/*添加新数据*/
			this->Content.push_back(new Td(
				Res,
				(Loop + 1) % this->Row == 0 ? this->Row : (Loop + 1) % this->Row,
				Loop + 1));//添加新数据
		}
	}
	/*重置标志位*/
	this->TotalPageNum = this->ContentTotal / this->Row;
	if (this->ContentTotal % this->Row)
	{
		this->TotalPageNum++;
	}
	this->PageNum = 1;
	this->BrowseYet = this->TotalPageNum;
	return true;
}

bool Table::SetLoadAgain()
{
	this->LoadContentFlag = 1;
	return true;
}

int Table::SetContentTotal(int ContentTotal)
{
	this->ContentTotal = ContentTotal;
	return 0;
}

