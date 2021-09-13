#include "select.h"


Select::Select(int POSITION_X, int POSITION_Y) :Widget("", POSITION_X, POSITION_Y)
{
	this->SetType("Select");
} 

int Select::Load()
{

	/*如果Value为空，把Value的值设为Option的第一个值*/
	vector<string>::iterator It;
	if (this->GetValue().empty()) {
		this->SetValue(*(this->Option.begin()));
	}
	/*获取控件宽度*/
	int Width = 0;
	for (It = this->Option.begin(); It != this->Option.end(); It++)
	{
		if ((*It).length()> Width)
		{
			Width = (*It).length();
		}
	}

	GoToXY(this->GetPOSITION_X() - 1,this->GetPOSITION_Y());
	cout << "<";
	cout << this->GetValue();
	GoToXY(this->GetPOSITION_X() + Width, this->GetPOSITION_Y());
	cout << ">";

	return 0;
}

int Select::GetCursor()
{
	HideCursor(0);
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	cout << this->GetValue();
	return OnClick();
}

int Select::LostCursor()
{
	OrgColor();
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	cout << this->GetValue();
	return 0;
}

int Select::OnClick()
{
	HANDLE hOut;
	//  获取输出流的句柄
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int Key;
	//将迭代器移到正确的位置
	vector<string>::iterator It = this->Option.begin();
	while (It != this->Option.end())
	{
		if (*It == this->GetValue())
		{
			break;
		}
		It++;
	}
	
	do
	{
		Key = NULL_KEY;
		while (_kbhit() == 0)
		{
			GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
			OrgColor();

			cout << this->GetValue();
			Sleep(500);

			if (_kbhit() != 0)
			{
				GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
				Intensity();
				cout << this->GetValue();
				break;
			}

			GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
			Intensity();

			cout << this->GetValue();
			Sleep(500);

		}

		Key = GetKey();
		if (Key == RIGHT_KEY)
		{
			if (It == this->Option.end()-1) //Option到最后一个
			{
				It = this->Option.begin();
				this->SetValue(*It);
				GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
				cout << this->GetValue();
			}
			else 
			{
				this->SetValue(*(++It));
				GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
				cout << this->GetValue();
			}
		}
		else if (Key == LEFT_KEY)
		{
			if (It == this->Option.begin())//Option到第一个
			{
				It = this->Option.end()-1;
				this->SetValue(*It);
				GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
				cout << this->GetValue();
			}
			else
			{
				this->SetValue(*(--It));
				GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
				cout << this->GetValue();
			}
		}
		else if (Key > 48 && Key <= 59)
		{
			LostCursor();
			return Key;
		}


	} while (Key != UP_KEY && Key != DOWN_KEY && Key != ESC_KEY && Key != TAB_KEY);

	LostCursor();
	return Key;
}

int Select::Refresh()
{
	Load();
	return 0;
}

int Select::AddOption(const string Option)
{
	this->Option.push_back(Option);
	return 0;
}

//int Select::AddOption(int Num, ...)
//{
//	va_list valist;
//	va_start(valist, Num);
//
//	for (int loop = 0; loop < Num; loop++)
//	{
//		this->Option.push_back(va_arg(valist, string));
//		
//	}
//	va_end(valist);
//	return 0;
//}

