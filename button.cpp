#include "button.h"

Button::Button(const string Value, int POSITION_X, int POSITION_Y) :Widget(Value, POSITION_X, POSITION_Y)
{
	this->SetType("Button");
}

int Button::Load()
{

	int Size = this->GetValue().size();
	/*©° ©´*/
	GoToXY(this->GetPOSITION_X() -2 , this->GetPOSITION_Y() -1 );
	cout << "©°";
	for (int Loop = 0; Loop < Size + 1; Loop++)
	{
		cout << " ";
	}
	/* */
	cout << "©´";
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	cout << " ";
	for (int Loop = 0; Loop < Size - 1; Loop++)
	{
		cout << " ";
	}
	cout << " ";
	/*©¸  ©¼*/
	GoToXY(this->GetPOSITION_X() - 2, this->GetPOSITION_Y() + 1);
	cout << "©¸";
	for (int Loop = 0; Loop < Size + 1; Loop++)
	{
		cout << " ";
	}
	cout << "©¼";
	/*Êä³öValue*/
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	cout << this->GetValue();
	return 0;
}

int Button::GetCursor()
{
	HideCursor(0);
	Intensity();
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	cout << this->GetValue();
	return OnClick();
}

int Button::LostCursor()
{
	OrgColor();
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	cout << this->GetValue();
	return 0;
}

int Button::OnClick()
{
	int Key ;
	while (1) 
	{
		Key = GetKey();
		if (Key == ENTER_KEY) 
		{
			LostCursor();
			return Key;
		}
		else if (Key == DOWN_KEY || Key == UP_KEY || Key == TAB_KEY || Key == ESC_KEY || Key == LEFT_KEY || Key == RIGHT_KEY)
		{
			LostCursor();
			return Key;
		}
		else if (Key > 48 && Key <= 59)
		{
			LostCursor();
			return Key;
		}
	}
}

int Button::Refresh()
{
	Load();
	return 0;
}




