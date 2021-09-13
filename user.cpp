#include "user.h"
User::User(const string ID, const string Name, const string PassWord, const string TYPE)
{
	this->ID.assign(ID);
	this->Name.assign(Name);
	this->PassWord.assign(PassWord);
	this->TYPE.assign(TYPE);
}

string User::GetID() const
{
	return this->ID;
}

string User::GetName() const
{
	return this->Name;
}

string User::GetPassWord() const
{
	return this->PassWord;
}

string User::GetTYPE() const
{
	return this->TYPE;
}

