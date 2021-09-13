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
		/*����մ���*/
		system("cls");
		/*���ش���*/
		/*�Ȼ����������*/
		GoToXY(this->PositionX, this->PositionY);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*������*/
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
		/*���ױ�*/
		GoToXY(this->PositionX, this->PositionY + this->Height);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*����ʾ��*/
		GoToXY(this->PositionX, this->PositionY + this->Height - 2);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*��������*/
		GoToXY(this->PositionX, this->PositionY + 4);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*�������ָ�*/
		for (int Loop = 0; Loop < 4; Loop++)
		{
			GoToXY(this->PositionX + this->Width * 2 / 3, this->PositionY + 1 + Loop);
			cout << "*";
		}
		/*������*/
		int TitleSize = this->Title.size();
		GoToXY(this->PositionX + this->Width * 2 / 3 / 2 - TitleSize / 2, this->PositionY + 2);
		cout << this->Title;
		/*��ʾ��¼��Ϣ*/
		/*��½��ɫ*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 1);
		cout << "�û���:" << USER_NAME;
		/*��ɫ���*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 2);
		cout << "�û�����:" << USER_TYPE;
		/*��½ʱ��*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 3);
		cout << "��¼ʱ��:" << DateToStringBySprit();
		/*���ؿؼ�*/
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
		/*����մ���*/
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			ClearArea(this->PositionX, this->PositionY + Loop, this->Width);
		}
		/*���ش���*/
		/*�Ȼ����������*/
		GoToXY(this->PositionX, this->PositionY);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*������*/
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
		/*���ױ�*/
		GoToXY(this->PositionX, this->PositionY + this->Height);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*��������*/
		GoToXY(this->PositionX, this->PositionY + 2);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*������*/
		int TitleSize = this->Title.size();
		GoToXY(this->PositionX + this->Width  / 2 - TitleSize / 2, this->PositionY + 1);
		cout << this->Title;
		/*���ؿؼ�*/
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
		/*ջΪ��*/
		if (Windows.empty())
		{
			/*����ǰҳ����ջ*/
			this->Init();
			Windows.push(this);
			this->Load();
		}
		/*����ý��滹δ����*/
		else if (Windows.top() != this)
		{
			/*����ϸ��������Ϣ�����ʾ�����ڴ�Ĳ���*/
			while (!Windows.top()->MsgBoxSt.empty())
			{
				delete Windows.top()->MsgBoxSt.top();
				Windows.top()->MsgBoxSt.pop();
			} 
			/*����ǰҳ����ջ*/
			this->Init();
			Windows.push(this);
			this->Load();
		}
		/*����ý����Ѵ���*/
		else if (Windows.top() == this)
		{
			this->Refresh();
		}
	}
	else if (this->Type == "MSGBOX")
	{
		/*ջΪ�ջ���ջ�������ڵ�ǰ��Ϣ��*/
		if (Windows.top()->MsgBoxSt.empty() || Windows.top()->MsgBoxSt.top() != this)
		{
			/*����Ϣ����ջ*/
			this->Init();
			Windows.top()->MsgBoxSt.push(this);
			this->Load();
			/*�������ʾ��*/
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
	/*���ָ�����Ϳؼ�*/
	vector<Widget*> WidgetRes;
	vector<Widget*>::iterator It = this->WidgetVec.begin();
	/*�ؼ�ֱ����ת�ؼ�*/
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
	/*�ؼ�ѭ��*/
	It = WidgetRes.begin();
	int State = NULL_KEY;
	while (State != ESC_KEY)
	{
 		this->ShowHint((*It)->GetHint());
		State = (*It)->GetCursor();
		/*����ֱ��ѡ��ؼ�*/
		if (State >48 && State <= 57)
		{
			/*û�ж�Ӧ�ؼ�*/
			if (State - 48 > JumpRes.size())
			{
				continue;
			}
			/*��ת���ؼ�*/
			It = WidgetRes.begin() + JumpRes.at(State - 48 - 1) - 1;
			continue;
		}
		if (State == RIGHT_KEY)
		{
			/*�����ж��Ƿ���ͬһY����*/
			vector<Widget*>::iterator TmpIt = It;
			/*��������һ��*/
			if (It == WidgetRes.end()-1) 
			{
				continue;
			}
			It++;
			int Flag = 0;
			while (It != WidgetRes.end())
			{
				
				/*����ҵ�*/
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
			/*�����ж��Ƿ���ͬһY����*/
			vector<Widget*>::iterator TmpIt = It;
			/*����ǵ�һ���ؼ�*/
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
				/*����ҵ�*/
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
		else if (State == UP_KEY)//����û������ƶ��ؼ�
		{
			if (It == WidgetRes.begin()) //����ؼ����˵�һ��
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
			if (It == WidgetRes.end()-1) //����ؼ��������һ��
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
			/*Res��0~9֮�� Ϊϵͳ��־λ*/
			/*Res��10~20֮�� Ϊ�û���־λ*/
			/*Res��48~57֮�� Ϊ�ؼ���־λ*/
			/*Res��5000���� Ϊ���ڱ�־λ*/
			int Res = this->Event(*It);
			if (Res>WIN_FLAG)//��ת����
			{
				return Res;
			}
			else if (Res == WIN_REFRESH)
			{
				this->Refresh();
			}
			else if (Res == WIN_NO_OPS)
			{
				/*��������*/
				continue;
			}
			else if (Res == WIN_EXIT)
			{
				/*��������������*/
				return WIN_EXIT;
			}
			/*���ڶ���������ڴ���*/
			else if (Res>= 10 && Res <=20) 
			{
				return Res;
			}
			/*�������õ�ָ��λ��*/
			else if(Res > 48 && Res <= 57)
			{
				/*û�ж�Ӧ�ؼ�*/
				if (Res - 48 > WidgetRes.size())
				{
					this->Refresh();
					continue;
				}
				It = WidgetRes.begin() + (Res - 48 - 1);
				this->Refresh();
			}
        	//�¼���1.������Ϣ��2��ѡ����->��ת��ҳ�棬3��ˢ��ҳ��
		}
		else if (State == ESC_KEY)
		{
			if (this->Type == "MSGBOX")
			{
			/*	this->Clear();*/
				return WIN_REFRESH;
			}
			/*���߽����Exit����*/
			int Res = this->Exit();
			if (Res == WIN_NO_OPS)
			{
				/*ȷ���˳�*/
				State =  ESC_KEY;
			}
			else 
			{
				/*�ط�ҳ�沢ˢ��ҳ��*/
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
		/*����մ���*/
		system("cls");
		/*���ش���*/
		/*�Ȼ����������*/
		GoToXY(this->PositionX, this->PositionY);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*������*/
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
		/*���ױ�*/
		GoToXY(this->PositionX, this->PositionY + this->Height);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*����ʾ��*/
		GoToXY(this->PositionX, this->PositionY + this->Height - 2);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*��������*/
		GoToXY(this->PositionX, this->PositionY + 4);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "* ";
		}
		/*�������ָ�*/
		for (int Loop = 0; Loop < 4; Loop++)
		{
			GoToXY(this->PositionX + this->Width * 2 / 3, this->PositionY + 1 + Loop);
			cout << "*";
		}
		/*������*/
		int TitleSize = this->Title.size();
		GoToXY(this->PositionX + this->Width * 2 / 3 / 2 - TitleSize / 2, this->PositionY + 2);
		cout << this->Title;
		/*��ʾ��¼��Ϣ*/
		/*��½��ɫ*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 1);
		cout << "�û���:" << USER_NAME;
		/*��ɫ���*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 2);
		cout << "�û�����:" << USER_TYPE;
		/*��½ʱ��*/
		GoToXY(this->PositionX + this->Width * 2 / 3 + 3, this->PositionY + 3);
		cout << "��¼ʱ��:" << DateToStringBySprit();
		/*���ؿؼ�*/
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
		/*����մ���*/
		for (int Loop = 0; Loop < this->Height; Loop++)
		{
			ClearArea(this->PositionX, this->PositionY + Loop, this->Width);
		}
		/*���ش���*/
		/*�Ȼ����������*/
		GoToXY(this->PositionX, this->PositionY);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*������*/
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
		/*���ױ�*/
		GoToXY(this->PositionX, this->PositionY + this->Height);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*��������*/
		GoToXY(this->PositionX, this->PositionY + 2);
		for (int Loop = 0; Loop < this->Width; Loop += 2)
		{
			cout << "+ ";
		}
		/*������*/
		int TitleSize = this->Title.size();
		GoToXY(this->PositionX + this->Width / 2 - TitleSize / 2, this->PositionY + 1);
		cout << this->Title;
		/*���ؿؼ�*/
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

