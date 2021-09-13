#include "goodsout.h"

GoodsOut::GoodsOut(const string ID, const string Name, const string Date, int InCount, string LocID)
{
	this->ID = ID;
	this->Name.assign(Name);
	this->Date.assign(Date);
	this->InCount = InCount;
	this->LocID.assign(LocID);
}

string GoodsOut::GetID() const
{
	return this->ID;
}

string GoodsOut::GetName() const
{
	return this->Name;
}

string GoodsOut::GetDate() const
{
	return this->Date;
}

int GoodsOut::GetCount() const
{
	return this->InCount;
}

string GoodsOut::GetLocID() const
{
	return this->LocID;
}
