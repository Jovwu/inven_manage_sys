#include "widget.h"
#include "window.h"
Window::Window(const string Title,int PositionX, int PositionY, int Width, int Height, const string Type)
{
	this->PositionX = PositionX;
	this->PositionY = PositionY;
	this->Width = Width;
	this->Height = Height;
	this->Title.assign(Title);
	this->Type.assign(Type);
	this->VanishFlag = 0;
}

int Window::Exit()
{
	return 0;
}

int Window::Add(Widget* widget)
{
	widget->SetPOSITION_X(widget->GetPOSITION_X()+this->PositionX);
	widget->SetPOSITION_Y(widget->GetPOSITION_Y() + this->PositionY);
	this->WidgetVec.push_back(widget);
	return 0;
}

int Window::Load()
{
	if (this->Type == "BASE") 
	{
		/*先清空窗口*/
		system("cls");
		/*加载窗口*/
		/*先画最上面的线*/
		GoToXY(this->PositionX, this->PositionY);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*画两边*/
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			GoToXY(this->PositionX, this->PositionY + 1 + Loop);
			cout << "*";
		}
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			GoToXY(this->PositionX + this->Width - 2, this->PositionY + 1 + Loop);
			cout << "*";
		}
		/*画底边*/
		GoToXY(this->PositionX, this->PositionY + this->Height);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*画提示栏*/
		GoToXY(this->PositionX, this->PositionY + this->Height - 2);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*画标题栏*/
		GoToXY(this->PositionX, this->PositionY + 4);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*标题栏分割*/
		for (int Loop = 0; Loop < 4; Loop++)
		{
			GoToXY(this->PositionX + this->Width * 2 / 3, this->PositionY + 1 + Loop);
			cout << "*";
		}
		/*画标题*/
		int TitleSize = this->Title.size();
		GoToXY(this->PositionX + this->Width * 2 / 3 / 2 - TitleSize / 2, this->PositionY + 2);
		cout << this->Title;
		/*显示登录信息*/
		/*登陆角色*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 1);
		cout << "用户名:" << USER_NAME;
		/*角色类别*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 2);
		cout << "用户类型:" << USER_TYPE;
		/*登陆时间*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 3);
		cout << "登录时间:" << DateToStringBySprit();
		/*加载控件*/
		vector<Widget*>::iterator It = this->WidgetVec.begin();
		while (It != this->WidgetVec.end())
		{
			(*It)->Load();
			It++;
		}
		return 0;
	}
	else if (this->Type == "MSGBOX") 
	{
		/*先清空窗口*/
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			ClearArea(this->PositionX, this->PositionY + Loop, this->Width);
		}
		/*加载窗口*/
		/*先画最上面的线*/
		GoToXY(this->PositionX, this->PositionY);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*画两边*/
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			GoToXY(this->PositionX, this->PositionY + 1 + Loop);
			cout << "+";
		}
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			GoToXY(this->PositionX + this->Width - 2, this->PositionY + 1 + Loop);
			cout << "+";
		}
		/*画底边*/
		GoToXY(this->PositionX, this->PositionY + this->Height);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*画标题栏*/
		GoToXY(this->PositionX, this->PositionY + 2);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*画标题*/
		int TitleSize = this->Title.size();
		GoToXY(this->PositionX + this->Width  / 2 - TitleSize / 2, this->PositionY + 1);
		cout << this->Title;
		/*加载控件*/
		vector<Widget*>::iterator It = this->WidgetVec.begin();
		while (It != this->WidgetVec.end())
		{
			(*It)->Load();
			It++;
		}
		return 0;
	}
	return 0;
}

int Window::Run()
{
	HideCursor(0);
	if (this->Type == "BASE") 
	{
		/*栈为空*/
		if (Windows.empty())
		{
			/*将当前页面入栈*/
			this->Init();
			Windows.push(this);
			this->Load();
		}
		/*如果该界面还未加载*/
		else if (Windows.top() != this)
		{
			/*清除上个界面的消息框和提示框在内存的残留*/
			while (!Windows.top()->MsgBoxSt.empty())
			{
				delete Windows.top()->MsgBoxSt.top();
				Windows.top()->MsgBoxSt.pop();
			} 
			/*将当前页面入栈*/
			this->Init();
			Windows.push(this);
			this->Load();
		}
		/*如果该界面已存在*/
		else if (Windows.top() == this)
		{
			this->Refresh();
		}
	}
	else if (this->Type == "MSGBOX")
	{
		/*栈为空或者栈顶不等于当前消息框*/
		if (Windows.top()->MsgBoxSt.empty() || Windows.top()->MsgBoxSt.top() != this)
		{
			/*将消息框入栈*/
			this->Init();
			Windows.top()->MsgBoxSt.push(this);
			this->Load();
			/*如果是提示框*/
			if (this->VanishFlag)
			{
				Sleep(HINT_BOX_SLEEP_TIME);
				return WIN_REFRESH;
			}
		}
		else if(Windows.top()->MsgBoxSt.top() == this)
		{
			this->Refresh();
		}
	}
	/*清除指定类型控件*/
	vector<Widget*> WidgetRes;
	vector<Widget*>::iterator It = this->WidgetVec.begin();
	/*控件直接跳转控件*/
	vector<int> JumpRes;
	int JumpCount = 0;
	while (It != this->WidgetVec.end())
	{
		if ((*It)->GetType() != "Label" && (*It)->GetType() != "Border")
		{
			JumpCount++;
			if ((*It)->GetType() == "Button")
			{
				JumpRes.push_back(JumpCount);
			}
			WidgetRes.push_back(*It);
		}
		It++;
	}
	/*控件循环*/
	It = WidgetRes.begin();
	int State = NULL_KEY;
	while (State != ESC_KEY)
	{
 		this->ShowHint((*It)->GetHint());
		State = (*It)->GetCursor();
		/*用于直接选择控件*/
		if (State >48 && State <= 57)
		{
			/*没有对应控件*/
			if (State - 48 > JumpRes.size())
			{
				continue;
			}
			/*跳转到控件*/
			It = WidgetRes.begin() + JumpRes.at(State - 48 - 1) - 1;
			continue;
		}
		if (State == RIGHT_KEY)
		{
			/*往下判断是否在同一Y轴上*/
			vector<Widget*>::iterator TmpIt = It;
			/*如果是最后一个*/
			if (It == WidgetRes.end()-1) 
			{
				continue;
			}
			It++;
			int Flag = 0;
			while (It != WidgetRes.end())
			{
				
				/*如果找到*/
				if ((*It)->GetPOSITION_Y() == (*TmpIt)->GetPOSITION_Y())
				{
					Flag = 1;
					break;
				}
				It++;
			}
			if (Flag == 1)
			{
				continue;
			}
			It = TmpIt;
		}
		else if (State == LEFT_KEY)
		{
			/*往上判断是否在同一Y轴上*/
			vector<Widget*>::iterator TmpIt = It;
			/*如果是第一个控件*/
			if (It == WidgetRes.begin()) 
			{
				continue;
			}
			int Flag = 0;
			int BeginFlag = 0;
			while (BeginFlag != 1)
			{
				It--;
				if (It == WidgetRes.begin())
				{
					BeginFlag = 1;
				}
				/*如果找到*/
				if ((*It)->GetPOSITION_Y() == (*TmpIt)->GetPOSITION_Y())
				{
					Flag = 1;
					break;
				}
			}
			if (Flag == 1)
			{
				continue;
			}
			It = TmpIt;
		}
		else if (State == UP_KEY)//如果用户往上移动控件
		{
			if (It == WidgetRes.begin()) //如果控件到了第一个
			{
				It == WidgetRes.end() - 1;
			}
			else
			{
				It--;
			}
		}
		else if (State == DOWN_KEY|| State == TAB_KEY)
		{
			if (It == WidgetRes.end()-1) //如果控件到了最后一个
			{
				It == WidgetRes.begin();
			}
			else 
			{
				It++;
			}
		}
		else if (State == ENTER_KEY)
		{
			/*Res在0~9之间 为系统标志位*/
			/*Res在10~20之间 为用户标志位*/
			/*Res在48~57之间 为控件标志位*/
			/*Res在5000以上 为窗口标志位*/
			int Res = this->Event(*It);
			if (Res>WIN_FLAG)//跳转窗口
			{
				return Res;
			}
			else if (Res == WIN_REFRESH)
			{
				this->Refresh();
			}
			else if (Res == WIN_NO_OPS)
			{
				/*继续操作*/
				continue;
			}
			else if (Res == WIN_EXIT)
			{
				/*用来跳出父窗口*/
				return WIN_EXIT;
			}
			/*可在多个派生窗口传递*/
			else if (Res>= 10 && Res <=20) 
			{
				return Res;
			}
			/*焦点重置到指定位置*/
			else if(Res > 48 && Res <= 57)
			{
				/*没有对应控件*/
				if (Res - 48 > WidgetRes.size())
				{
					this->Refresh();
					continue;
				}
				It = WidgetRes.begin() + (Res - 48 - 1);
				this->Refresh();
			}
        	//事件：1.弹出消息框，2。选择功能->跳转到页面，3。刷新页面
		}
		else if (State == ESC_KEY)
		{
			if (this->Type == "MSGBOX")
			{
			/*	this->Clear();*/
				return WIN_REFRESH;
			}
			/*先走界面的Exit方法*/
			int Res = this->Exit();
			if (Res == WIN_NO_OPS)
			{
				/*确定退出*/
				State =  ESC_KEY;
			}
			else 
			{
				/*重返页面并刷新页面*/
				this->Refresh();
				State = NULL_KEY;
			}
		}
		else if (State == NULL_KEY)
		{
			continue;
		}
	}
	return State;
}

int Window::Refresh()
{
	if (this->Type == "BASE")
	{
		/*先清空窗口*/
		system("cls");
		/*加载窗口*/
		/*先画最上面的线*/
		GoToXY(this->PositionX, this->PositionY);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*画两边*/
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			GoToXY(this->PositionX, this->PositionY + 1 + Loop);
			cout << "*";
		}
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			GoToXY(this->PositionX + this->Width - 2, this->PositionY + 1 + Loop);
			cout << "*";
		}
		/*画底边*/
		GoToXY(this->PositionX, this->PositionY + this->Height);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*画提示栏*/
		GoToXY(this->PositionX, this->PositionY + this->Height - 2);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*画标题栏*/
		GoToXY(this->PositionX, this->PositionY + 4);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*标题栏分割*/
		for (int Loop = 0; Loop < 4; Loop++)
		{
			GoToXY(this->PositionX + this->Width * 2 / 3, this->PositionY + 1 + Loop);
			cout << "*";
		}
		/*画标题*/
		int TitleSize = this->Title.size();
		GoToXY(this->PositionX + this->Width * 2 / 3 / 2 - TitleSize / 2, this->PositionY + 2);
		cout << this->Title;
		/*显示登录信息*/
		/*登陆角色*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 1);
		cout << "用户名:" << USER_NAME;
		/*角色类别*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 2);
		cout << "用户类型:" << USER_TYPE;
		/*登陆时间*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 3);
		cout << "登录时间:" << DateToStringBySprit();
		/*加载控件*/
		vector<Widget*>::iterator It = this->WidgetVec.begin();
		while (It != this->WidgetVec.end())
		{
			(*It)->Refresh();
			It++;
		}
		return 0;
	}
	else if (this->Type == "MSGBOX")
	{
		/*先清空窗口*/
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			ClearArea(this->PositionX, this->PositionY + Loop, this->Width);
		}
		/*加载窗口*/
		/*先画最上面的线*/
		GoToXY(this->PositionX, this->PositionY);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*画两边*/
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			GoToXY(this->PositionX, this->PositionY + 1 + Loop);
			cout << "+";
		}
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			GoToXY(this->PositionX + this->Width - 2, this->PositionY + 1 + Loop);
			cout << "+";
		}
		/*画底边*/
		GoToXY(this->PositionX, this->PositionY + this->Height);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*画标题栏*/
		GoToXY(this->PositionX, this->PositionY + 2);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*画标题*/
		int TitleSize = this->Title.size();
		GoToXY(this->PositionX + this->Width / 2 - TitleSize / 2, this->PositionY + 1);
		cout << this->Title;
		/*加载控件*/
		vector<Widget*>::iterator It = this->WidgetVec.begin();
		while (It != this->WidgetVec.end())
		{
			(*It)->Refresh();
			It++;
		}
		return 0;
	}
	return 0;
}

int Window::ShowHint(const string Hint)
{
	if(this->Type == "BASE")
	{
		HideCursor(0);
		ClearArea(this->PositionX + 2, this->PositionY + this->Height - 1, this->Width - 4);
		GoToXY(this->PositionX + 2, this->PositionY + this->Height - 1);
		cout << Hint;
		return 0;
	}
	else if (this->Type == "MSGBOX")
	{
		return 0;
	}
}

