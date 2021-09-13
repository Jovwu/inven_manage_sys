#include "widget.h"
Widget::Widget(const string Value, int POSITION_X, int POSITION_Y)
{
	this->Value.assign(Value);
	this->POSITION_X = POSITION_X;
	this->POSITION_Y = POSITION_Y;
}

int Widget::Load()
{
	return 0;
}

int Widget::GetCursor()
{
	return 0;
}

int Widget::LostCursor()
{
	return 0;
}

int Widget::OnClick()
{
	return 0;
}

int Widget::GetPOSITION_X() const
{
	return this->POSITION_X;
}

int Widget::GetPOSITION_Y() const
{
	return this->POSITION_Y;
}

int Widget::SetValue(string Value)
{
	this->Value.assign(Value);
	return 0;
}

string Widget::GetValue() const
{
	return this->Value;
}

int Widget::SetType(string TYPE)
{
	this->TYPE.assign(TYPE);
	return 0;
}

string Widget::GetType() const
{
	return this->TYPE;
}

int Widget::SetHint(string HINT)
{
	this->HINT.assign(HINT);
	return 0;
}

string Widget::GetHint() const
{
	return this->HINT;
}

int Widget::SetPOSITION_X(int POSITION_X)
{
	this->POSITION_X = POSITION_X;
	return 0;
}

int Widget::SetPOSITION_Y(int POSITION_Y)
{
	this->POSITION_Y = POSITION_Y;
	return 0;
}

