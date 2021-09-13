#include "edit.h"
Edit::Edit(int POSITION_X, int POSITION_Y, const string TEXTTYPE, int Length) :Widget("", POSITION_X, POSITION_Y)
{
	this->TEXTTYPE.assign(TEXTTYPE);
	this->Length = Length;
	this->GetValue().resize(this->Length);
	
}

int Edit::Load()
{
	GoToXY(this->GetPOSITION_X() - 1, this->GetPOSITION_Y());
	printf("[");
	GoToXY(this->GetPOSITION_X() + this->Length + 1, this->GetPOSITION_Y());
	printf("]");
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	return 0;
}

int Edit::GetCursor()
{
	//先显示已有的内容
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	if (!this->GetValue().empty())//如果文本已被编辑,在屏幕上打印
	{
		if (this->TEXTTYPE == "PASSWORD") 
		{
			for (int Loop=0;Loop<this->GetValue().size();Loop++) 
			{
				cout << "*";
			}
		}
		else
		{
			cout << this->GetValue();
		}
	}
	return OnClick();
}

int Edit::LostCursor()
{
	HideCursor(0);
	return 0;
}

int Edit::OnClick()
{
	if (this->TEXTTYPE == "NOTCHINESE")
	{
		return this->NotChinese();
	}
	else if (this->TEXTTYPE == "ONLYCHINESE")
	{
		return this->OnlyChinese();
	}
	else if (this->TEXTTYPE == "PASSWORD")
	{
		return this->PassWord();
	}
	else if (this->TEXTTYPE == "ONLYFIGURE")
	{
		return this->OnlyFigure();
	}
	else if (this->TEXTTYPE == "UNLIMITED")
	{
		return this->Unlimited();
	}
	return 0;
}

int Edit::OnlyChinese()
{
	HideCursor(1);
	char Key = ' ';
	int Dirty = this->GetValue().size();//文本已写数量
	//获得键盘输入
	for (int Cursor = Dirty; Cursor < this->Length + 1; Cursor++)
	{
		Key = _getch();//获取按键输入
		//当输入方向键
		if (Key == CTR_KEY)
		{
			switch (_getch())
			{
			case UP_KEY:
				return UP_KEY;
			case DOWN_KEY:
				return DOWN_KEY;
			case LEFT_KEY:
				return LEFT_KEY;
			case RIGHT_KEY:
				return RIGHT_KEY;
			default:
				break;
			}
			Cursor--;
			continue;//排除异常
		}
		else if (Key == ESC_KEY)
		{
			return ESC_KEY;//ESC键退出
		}
		else if (Key == TAB_KEY)
		{
			return TAB_KEY;
		}
		//当光标在行头
		if (Cursor == 0)
		{
			if (Key == DEL_KEY || Key == ENTER_KEY)//无法提交,无法进行删除
			{
				Cursor--;
				continue;
			}
		}
		//当光标在行尾
		if (Cursor == this->Length)
		{
			if (Key == DEL_KEY)//进行删除
			{
				putchar('\b');
				putchar('\b');
				putchar(' ');
				putchar(' ');
				putchar('\b');
				putchar('\b');
				Cursor -= 3;
				this->SetValue(this->GetValue().substr(0, Dirty - 2));
				Dirty -= 2;
				continue;
			}
			else if (Key == ENTER_KEY)//提交
			{
				return ENTER_KEY;
			}
			//输入为字符
			Cursor--;//字数到达上限,无法继续输入
			continue;
		}
		//当光标在行中
		if (Key == DEL_KEY)//删除
		{
			putchar('\b');
			putchar('\b');
			putchar(' ');
			putchar(' ');
			putchar('\b');
			putchar('\b');
			Cursor -= 3;
			this->SetValue(this->GetValue().substr(0, Dirty-2));
			Dirty -= 2;
			continue;
		}
		else if (Key == ENTER_KEY)//提交
		{
			return ENTER_KEY;
		}
		else//排除特殊情况，正常输入
		{
			//除了中文，其他的排除
			if (!((unsigned int)Key> 160))
			{
				Cursor--;
				continue;
			}
			this->SetValue(this->GetValue() + Key);
			putchar(Key);
			Key = _getch();
			this->SetValue(this->GetValue() + Key);
			Dirty+=2;
			Cursor++;
			putchar(Key);
			continue;
		}
	}
	return NULL_KEY;
}

int Edit::NotChinese()
{
	HideCursor(1);
	char Key = ' ';
	int Dirty = this->GetValue().size();//文本已写数量
	//获得键盘输入
	for (int Cursor = Dirty; Cursor < this->Length + 1; Cursor++)
	{
		Key = _getch();//获取按键输入
		//当输入方向键
		if (Key == CTR_KEY)
		{
			switch (_getch())
			{
			case UP_KEY:
				return UP_KEY;
			case DOWN_KEY:
				return DOWN_KEY;
			case LEFT_KEY:
				return LEFT_KEY;
			case RIGHT_KEY:
				return RIGHT_KEY;
			default:
				break;
			}
			Cursor--;
			continue;//排除异常
		}
		else if (Key == ESC_KEY)
		{
			return ESC_KEY;//ESC键退出
		}
		else if (Key == TAB_KEY)
		{
			return TAB_KEY;
		}
		//当光标在行头
		if (Cursor == 0)
		{
			if (Key == DEL_KEY || Key == ENTER_KEY)//无法提交,无法进行删除
			{
				Cursor--;
				continue;
			}
		}
		//当光标在行尾
		if (Cursor == this->Length)
		{
			if (Key == DEL_KEY)//进行删除
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				Cursor -= 2;
				this->SetValue(this->GetValue().substr(0, --Dirty));
				continue;
			}
			else if (Key == ENTER_KEY)//提交
			{
				return ENTER_KEY;
			}
			//输入为字符
			Cursor--;//字数到达上限,无法继续输入
			continue;
		}
		//当光标在行中
		if (Key == DEL_KEY)//删除
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			Cursor -= 2;
			this->SetValue(this->GetValue().substr(0, --Dirty));
			continue;
		}
		else if (Key == ENTER_KEY)//提交
		{
			return ENTER_KEY;
		}
		else//排除特殊情况，正常输入
		{
			//除了数字和字母，其他的排除
			if (!((Key >= 48 && Key <= 59) || (Key >= 65 && Key <= 90) || (Key >= 97 && Key <= 122)))
			{
				Cursor--;
				continue;
			}
			this->SetValue(this->GetValue()+ Key);
			Dirty++;
			putchar(Key);
			continue;
		}
	}
	return NULL_KEY;
}

int Edit::OnlyFigure()
{
	HideCursor(1);
	char Key = ' ';
	int Dirty = this->GetValue().size();//文本已写数量
	//获得键盘输入
	for (int Cursor = Dirty; Cursor < this->Length + 1; Cursor++)
	{
		Key = _getch();//获取按键输入
		//当输入方向键
		if (Key == CTR_KEY)
		{
			switch (_getch())
			{
			case UP_KEY:
				return UP_KEY;
			case DOWN_KEY:
				return DOWN_KEY;
			case LEFT_KEY:
				return LEFT_KEY;
			case RIGHT_KEY:
				return RIGHT_KEY;
			default:
				break;
			}
			Cursor--;
			continue;//排除异常
		}
		else if (Key == ESC_KEY)
		{
			return ESC_KEY;//ESC键退出
		}
		else if (Key == TAB_KEY)
		{
			return TAB_KEY;
		}
		//当光标在行头
		if (Cursor == 0)
		{
			if (Key == DEL_KEY || Key == ENTER_KEY)//无法提交,无法进行删除
			{
				Cursor--;
				continue;
			}
		}
		//当光标在行尾
		if (Cursor == this->Length)
		{
			if (Key == DEL_KEY)//进行删除
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				Cursor -= 2;
				this->SetValue(this->GetValue().substr(0, --Dirty));
				continue;
			}
			else if (Key == ENTER_KEY)//提交
			{
				return ENTER_KEY;
			}
			//输入为字符
			Cursor--;//字数到达上限,无法继续输入
			continue;
		}
		//当光标在行中
		if (Key == DEL_KEY)//删除
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			Cursor -= 2;
			this->SetValue(this->GetValue().substr(0, --Dirty));
			continue;
		}
		else if (Key == ENTER_KEY)//提交
		{
			return ENTER_KEY;
		}
		else//排除特殊情况，正常输入
		{
			//除了数字，其他的排除
			if (!(Key >= 48 && Key <= 57))
			{
				Cursor--;
				continue;
			}
			this->SetValue(this->GetValue() + Key);
			Dirty++;
			putchar(Key);
			continue;
		}
	}
	return NULL_KEY;
}

int Edit::PassWord()
{
	HideCursor(1);
	char Key = ' ';
	int Dirty = this->GetValue().size();//文本已写数量
	//获得键盘输入
	for (int Cursor = Dirty; Cursor < this->Length + 1; Cursor++)
	{
		Key = _getch();//获取按键输入
		//当输入方向键
		if (Key == CTR_KEY)
		{
			switch (_getch())
			{
			case UP_KEY:
				return UP_KEY;
			case DOWN_KEY:
				return DOWN_KEY;
			case LEFT_KEY:
				return LEFT_KEY;
			case RIGHT_KEY:
				return RIGHT_KEY;
			default:
				break;
			}
			Cursor--;
			continue;//排除异常
		}
		else if (Key == ESC_KEY)
		{
			return ESC_KEY;//ESC键退出
		}
		else if (Key == TAB_KEY)
		{
			return TAB_KEY;
		}
		//当光标在行头
		if (Cursor == 0)
		{
			if (Key == DEL_KEY || Key == ENTER_KEY)//无法提交,无法进行删除
			{
				Cursor--;
				continue;
			}
		}
		//当光标在行尾
		if (Cursor == this->Length)
		{
			if (Key == DEL_KEY)//进行删除
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				Cursor -= 2;
				this->SetValue(this->GetValue().substr(0, --Dirty));
				continue;
			}
			else if (Key == ENTER_KEY)//提交
			{
				return ENTER_KEY;
			}
			//输入为字符
			Cursor--;//字数到达上限,无法继续输入
			continue;
		}
		//当光标在行中
		if (Key == DEL_KEY)//删除
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			Cursor -= 2;
			this->SetValue(this->GetValue().substr(0, --Dirty));
			continue;
		}
		else if (Key == ENTER_KEY)//提交
		{
			return ENTER_KEY;
		}
		else//排除特殊情况，正常输入
		{
			//除了数字和字母，其他的排除
			if (!((Key >= 48 && Key <= 59) || (Key >= 65 && Key <= 90) || (Key >= 97 && Key <= 122)))
			{
				Cursor--;
				continue;
			}
			this->SetValue(this->GetValue() + Key);
			Dirty++;
			putchar('*');
			continue;
		}
	}
	return NULL_KEY;
}

int Edit::Unlimited()
{
	HideCursor(1);
	char Key = ' ';
	int Dirty = this->GetValue().size();//文本已写数量
	//获得键盘输入
	for (int Cursor = Dirty; Cursor < this->Length + 1; Cursor++)
	{
		Key = _getch();//获取按键输入
		//当输入方向键
		if (Key == CTR_KEY)
		{
			switch (_getch())
			{
			case UP_KEY:
				return UP_KEY;
			case DOWN_KEY:
				return DOWN_KEY;
			case LEFT_KEY:
				return LEFT_KEY;
			case RIGHT_KEY:
				return RIGHT_KEY;
			default:
				break;
			}
			Cursor--;
			continue;//排除异常
		}
		else if (Key == ESC_KEY)
		{
			return ESC_KEY;//ESC键退出
		}
		else if (Key == TAB_KEY)
		{
			return TAB_KEY;
		}
		//当光标在行头
		if (Cursor == 0)
		{
			if (Key == DEL_KEY || Key == ENTER_KEY)//无法提交,无法进行删除
			{
				Cursor--;
				continue;
			}
		}
		//当光标在行尾
		if (Cursor == this->Length)
		{
			if (Key == DEL_KEY)//进行删除
			{
				if (((unsigned int)this->GetValue().at(this->GetValue().size() - 1) > 160))
				{
					putchar('\b');
					putchar('\b');
					putchar(' ');
					putchar(' ');
					putchar('\b');
					putchar('\b');
					Cursor -= 3;
					this->SetValue(this->GetValue().substr(0, Dirty - 2));
					Dirty -= 2;
					continue;
				}
				
					putchar('\b');
					putchar(' ');
					putchar('\b');
					Cursor -= 2;
					this->SetValue(this->GetValue().substr(0, --Dirty));
					continue;
			}
			else if (Key == ENTER_KEY)//提交
			{
				return ENTER_KEY;
			}
			//输入为字符
			Cursor--;//字数到达上限,无法继续输入
			continue;
		}
		//当光标在行中
		if (Key == DEL_KEY)//删除
		{
			if (((unsigned int)this->GetValue().at(this->GetValue().size() - 1) > 160))
			{
				putchar('\b');
				putchar('\b');
				putchar(' ');
				putchar(' ');
				putchar('\b');
				putchar('\b');
				Cursor -= 3;
				this->SetValue(this->GetValue().substr(0, Dirty - 2));
				Dirty -= 2;
				continue;
			}
			
				putchar('\b');
				putchar(' ');
				putchar('\b');
				Cursor -= 2;
				this->SetValue(this->GetValue().substr(0, --Dirty));
				continue;
		
		}
		else if (Key == ENTER_KEY)//提交
		{
			return ENTER_KEY;
		}
		else//排除特殊情况，正常输入
		{
			//除了中文
			if ((unsigned int)Key > 160)
			{
				this->SetValue(this->GetValue() + Key);
				putchar(Key);
				Key = _getch();
				this->SetValue(this->GetValue() + Key);
				Dirty += 2;
				Cursor++;
				putchar(Key);
				continue;
			}
			
				this->SetValue(this->GetValue() + Key);
				Dirty++;
				putchar(Key);
				continue;
			
		}
	}
	return NULL_KEY;
}

int Edit::Refresh()
{
	Load();
	GoToXY(this->GetPOSITION_X(), this->GetPOSITION_Y());
	if (!this->GetValue().empty())//如果文本已被编辑,在屏幕上打印
	{
		if (this->TEXTTYPE == "PASSWORD")
		{
			for (int Loop = 0; Loop < this->GetValue().size(); Loop++)
			{
				cout << "*";
			}
		}
		else
		{
			cout << this->GetValue();
		}
	}
	return 0;
}
