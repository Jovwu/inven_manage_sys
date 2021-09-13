#include "td.h"
Td::Td(const vector<string> Content, int CurrentPageLineNum, int FileNum)
{
	this->ClickFlag = 0;
	this->Content = Content;
	this->CurrentPageLineNum = CurrentPageLineNum;
	this->FileNum = FileNum;

}

vector<string> Td::GetContent() const
{
	return this->Content;
}

int Td::GetClickFlag() const
{
	return this->ClickFlag;
}

int Td::GetCurrentPageLineNum() const
{
	return this->CurrentPageLineNum;
}

int Td::GetFileNum() const
{
	return this->FileNum;
}

bool Td::SetContent(vector<string> Content)
{
	this->Content.assign(Content.begin(), Content.end());
	return true;
}

bool Td::SetClickFlag(int ClickFlag)
{
	if (ClickFlag == 1 || ClickFlag == 0)
	{
		this->ClickFlag = ClickFlag;
		return true;
	}
	else
	{
		return false;
	}
}
