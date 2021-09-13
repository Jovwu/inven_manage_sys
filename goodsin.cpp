#include "goodsin.h"

GoodsIn::GoodsIn(const string ID, const string Name, const string Date, int InCount, string LocID)
{
	this->ID = ID;
	this->Name.assign(Name);
	this->Date.assign(Date);
	this->InCount = InCount;
	this->LocID.assign(LocID);
}

string GoodsIn::GetID() const
{
	return this->ID;
}

string GoodsIn::GetName() const
{
	return this->Name;
}

string GoodsIn::GetDate() const
{
	return this->Date;
}

int GoodsIn::GetCount() const
{
	return this->InCount;
}

string GoodsIn::GetLocID() const
{
	return this->LocID;
}
