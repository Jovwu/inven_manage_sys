#include "login.h"

Login::Login():Window("�û���¼����",WIN_POS_X,WIN_POS_Y,WIN_WIDTH,WIN_HEIGHT,"BASE")
{
}

int Login::Init()
{
	this->UserTypeSelect->SetHint("��ѡ�����Ľ�ɫ����");
	this->UserTypeSelect->AddOption("����Ա");
	this->UserTypeSelect->AddOption("�̵�Ա");

	this->UserIDEdit->SetHint("�����������˺�");
	this->UserPswEdit->SetHint("��������������");
	this->LoginButton->SetHint("��¼����ɫ���ҳ����в���");
	this->RegButton->SetHint("ע��һ�����˻�");

	this->Add(this->UserType);
	this->Add(this->UserTypeSelect);
	this->Add(this->UserID);
	this->Add(this->UserIDEdit);
	this->Add(this->UserPsw);
	this->Add(this->UserPswEdit);
	this->Add(this->LoginButton);
	this->Add(this->RegButton);

	return 0;
}

int Login::Exit()
{
	
	if ((new LoginExitBox())->Run() == WIN_EXIT)
	{
		/*ȷ���˳�*/
		return WIN_NO_OPS;
	}
	else
	{
		return WIN_REFRESH;
	}
}

int Login::Event(Widget* Obj)
{
	if (Obj == this->LoginButton)
	{
		return this->LoginButtonEvent();
	}
	else if( Obj == this->RegButton)
	{
		return this->RegButtonEvent();
	}
	return WIN_NO_OPS;
}


int Login::LoginButtonEvent()
{
	UserFile* UF = new UserFile();
	/*�û���Ϊ��*/
	if (this->UserIDEdit->GetValue().empty()) 
	{
		(new HintWin("�û�ID����Ϊ��!"))->Run();
		return WIN_CUR_POS_2;
	}
	/*����Ϊ��*/
	else if (this->UserPswEdit->GetValue().empty())
	{
		(new HintWin("�û����벻��Ϊ��!"))->Run();
		return WIN_CUR_POS_3;
	}
	/*�û�������*/
	else if (UF->Select(1,this->UserIDEdit->GetValue()).empty())
	{
		(new HintWin("�û�������!"))->Run();
		this->UserIDEdit->SetValue("");
		this->UserPswEdit->SetValue("");
		return WIN_CUR_POS_2;
	}
	/*���벻��ȷ*/
	else if (UF->SelectSingle(1, this->UserIDEdit->GetValue(),3) != this->UserPswEdit->GetValue())
	{
		this->UserPswEdit->SetValue("");
		(new HintWin("�û����벻��ȷ!"))->Run();
		return WIN_CUR_POS_3;
	}
	/*��ɫ��֤*/
	else 
	{
		/*�̵�Ա*/
		if (this->UserTypeSelect->GetValue() == "�̵�Ա")
		{
			/*�����̵�Ա�����֤*/
			if (UF->SelectSingle(1, this->UserIDEdit->GetValue(), 4) != "�̵�Ա")
			{
				(new HintWin("�������̵�Ա!"))->Run();
				return WIN_CUR_POS_1;
			}
			/*�޸�config.h*/
			USER_ID = this->UserIDEdit->GetValue();
			USER_NAME = UF->SelectSingle(1, this->UserIDEdit->GetValue(), 2);
			USER_TYPE = this->UserTypeSelect->GetValue();
			/*���ҳ��ֵ*/
			this->UserIDEdit->SetValue("");
			this->UserPswEdit->SetValue("");
			/*��ת���̵�Ա����*/
			return WIN_CHECK_MENU;
		}
		/*����Ա*/
		else if (this->UserTypeSelect->GetValue() == "����Ա")
		{
			/*���й���Ա�����֤*/
			if (UF->SelectSingle(1, this->UserIDEdit->GetValue(), 4) != "����Ա")
			{
				(new HintWin("�����ǹ���Ա!"))->Run();
				return WIN_CUR_POS_1;
			}
			/*�޸�config.h*/
			USER_ID = this->UserIDEdit->GetValue();
			USER_NAME = UF->SelectSingle(1, this->UserIDEdit->GetValue(), 2);
			USER_TYPE = this->UserTypeSelect->GetValue();
			/*���ҳ��ֵ*/
			this->UserIDEdit->SetValue("");
			this->UserPswEdit->SetValue("");
			/*��ת������Ա����*/
			return WIN_ADMIN_MENU;
		}
	}
	return WIN_REFRESH;
}

int Login::RegButtonEvent()
{
	return WIN_REG;
}
/****************************************************/
LoginExitBox::LoginExitBox() :Window("��ʾ", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int LoginExitBox::Init()
{
	this->Add(this->Msg);
	this->Add(this->OK);
	this->Add(this->NO);
	return 0;
}

int LoginExitBox::Event(Widget* Obj)
{
	if (Obj == this->OK)
	{
		return WIN_EXIT;
	}
	else if (Obj == this->NO)
	{
		/*�ղ���*//*���޸�*/
		return EXIT_CANCEL;
	}
	return 0;

}