#include "checkinfo.h"

CheckInfo::CheckInfo(const string User, const string Goods, int OrgCount, int CheckCount)
{
	
	this->User.assign(User);
	this->Goods.assign(Goods);
	this->OrgCount = OrgCount;
	this->CheckCount = CheckCount;
	this->Difference = abs(this->OrgCount - this->CheckCount);
	this->Analyse.assign("Î´¸´ÅÌ");
}



string CheckInfo::GetUser() const
{
	return this->User;
}

int CheckInfo::GetDifference() const
{
	return this->Difference;
}


string CheckInfo::GetGoods() const
{
	return this->Goods;
}

int CheckInfo::GetOrgCount() const
{
	return this->OrgCount;
}

int CheckInfo::GetCheckCount() const
{
	return this->CheckCount;
}

string CheckInfo::GetAnalyse() const
{
	return this->Analyse;
}

bool CheckInfo::SetDifference()
{
	this->Difference = abs(this->OrgCount - this->CheckCount);
	return true;
}

bool CheckInfo::SetDifference(int Difference)
{
	this->Difference = Difference;
	return true;
}

bool CheckInfo::SetCheckCount(int CheckCount)
{
	if (CheckCount<0)
	{
		return false;
	}
	else
	{
		this->CheckCount = CheckCount;
		return true;
	}
}

bool CheckInfo::SetAnalyse(string Analyse)
{
	this->Analyse.assign(Analyse);
	return true;
}



