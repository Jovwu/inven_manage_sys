#include "label.h"

Label::Label(const string Value, int POSITION_X, int POSITION_Y) :Widget(Value, POSITION_X, POSITION_Y)
{
	this->SetType("Label");
}

int Label::Load()
{
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	cout << this->GetValue();
	return 0;
}

int Label::GetCursor()
{
	return OnClick();
}

int Label::LostCursor()
{
	return 0;
}

int Label::OnClick()
{
	LostCursor();
	return 0;
}

int Label::Refresh()
{
	Load();
	return 0;
}
