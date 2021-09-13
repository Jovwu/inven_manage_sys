#include "goods.h"

Goods::Goods(const string ID, const string Name, const string Type, double Price, int Count, string LocID)
{
	this->ID.assign(ID);
	this->Name.assign(Name);
	this->Type.assign(Type);
	this->Price = Price;
	this->Count = Count;
	this->LocID.assign(LocID);
}

int Goods::SetPrice(double Price)
{
	this->Price = Price;
	return 0;
}

int Goods::SetCount(int Count)
{
	this->Count = Count;
	return 0;
}

string Goods::GetID() const
{
	return this->ID;
}

string Goods::GetName() const
{
	return this->Name;
}

string Goods::GetType() const
{
	return this->Type;
}

double Goods::GetPrice() const
{
	return this->Price;
}

int Goods::GetCount() const
{
	return this->Count;
}

string Goods::GetLocID() const
{
	return this->LocID;
}
