#include "border.h"

Border::Border(int POSITION_X, int POSITION_Y, int Width, int Height) :Widget("", POSITION_X, POSITION_Y)
{
	this->SetType("Border");
	this->Width = Width;
	this->Height = Height;
}

int Border::Load()
{
	HideCursor(0);
	/*先画最上面的线*/
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	for (int Loop = 0; Loop < this->Width; Loop += 2)
	{
		cout << "+ ";
	}
	/*画两边*/
	for (int Loop = 0; Loop < this->Height; Loop++)
	{
		GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y() + 1 + Loop);
		cout << "+";
	}
	for (int Loop = 0; Loop < this->Height; Loop++)
	{
		GoToXY(this->GetPOSITION_X() + this->Width - 2, this->GetPOSITION_Y() + 1 + Loop);
		cout << "+";
	}
	/*画底边*/
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y() + this->Height);
	for (int Loop = 0; Loop < this->Width; Loop += 2)
	{
		cout << "+ ";
	}
	return 0;
}

int Border::GetCursor()
{
	return 0;
}

int Border::LostCursor()
{
	return 0;
}

int Border::OnClick()
{
	return 0;
}

int Border::Refresh()
{
	this->Load();
	return 0;
}
