#include "checknote.h"

CheckNote::CheckNote(const string ID)
{
	this->ID.assign(ID);
	this->Reverse.assign("δ����");
	this->Explain.assign("��");
}

string CheckNote::GetID() const
{
	return this->ID;
}

string CheckNote::GetReverse() const
{
	return this->Reverse;
}

string CheckNote::GetExplain() const
{
	return this->Explain;
}

bool CheckNote::SetExplain(const string Explain)
{
	this->Explain.assign(Explain);
	return true;
}

bool CheckNote::SetReverse(string Reverse)
{
	this->Reverse.assign(Reverse);
	return true;
	
}
