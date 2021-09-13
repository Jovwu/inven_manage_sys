#include "reg.h"

Reg::Reg():Window("�û�ע�����", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int Reg::Init()
{
	/*�û��˺�Ϊ�̶�ֵ*/
	UserFile* UF = new UserFile();
	UF->Count();
	this->UserIDValue->SetValue(to_string(UF->Count()+1001));
	delete UF;

	this->UserTypeSelect->SetHint("��ѡ������ע���ɫ");
	this->UserTypeSelect->AddOption("����Ա");
	this->UserTypeSelect->AddOption("�̵�Ա");

	this->UserNameEdit->SetHint("��������������(��������)");
	this->UserPswEdit->SetHint("��������������");
	this->RegButton->SetHint("ע��һ�����˻�");
	this->UserPswAgainEdit->SetHint("���ٴ�ȷ������");

	this->Add(this->UserType);
	this->Add(this->UserTypeSelect);
	this->Add(this->UserID);
	this->Add(this->UserIDValue);
	this->Add(this->UserName);
	this->Add(this->UserNameEdit);
	this->Add(this->UserPsw);
	this->Add(this->UserPswEdit);
	this->Add(this->UserPswAgain);
	this->Add(this->UserPswAgainEdit);
	this->Add(this->RegButton);

	return 0;
}

int Reg::Event(Widget* Obj)
{
	if (Obj == this->RegButton)
	{
		return this->RegButtonEvent();
	}
	return WIN_NO_OPS;
}


int Reg::RegButtonEvent()
{
	/*�û���Ϊ��*/
	if (this->UserNameEdit->GetValue().empty())
	{
		(new HintWin("�û�������Ϊ��!"))->Run();
		return WIN_CUR_POS_2;
	}
	/*����Ϊ��*/
	else if (this->UserPswEdit->GetValue().empty())
	{
		(new HintWin("�û����벻��Ϊ��!"))->Run();
		return WIN_CUR_POS_3;
	}
	/*ȷ������Ϊ��*/
	else if (this->UserPswAgainEdit->GetValue().empty())
	{
		(new HintWin("���ٴ���������!"))->Run();
		return WIN_CUR_POS_4;
	}
	/*�����������벻��ȷ*/
	else if (this->UserPswEdit->GetValue() != this->UserPswAgainEdit->GetValue())
	{
		(new HintWin("ǰ���������벻һ��!"))->Run();
		this->UserPswAgainEdit->SetValue("");
		return WIN_CUR_POS_4;
	}
	/*����ע������*/
	else
	{
		UserFile* UF = new UserFile();
		User* NewUser = new User(
			this->UserIDValue->GetValue(),
			this->UserNameEdit->GetValue(),
			this->UserPswEdit->GetValue(),
			this->UserTypeSelect->GetValue()
		);
		/*�ж�ע���Ƿ�ɹ�*/
		/*ע��ɹ�*/
		if (UF->AppendUser(NewUser))
		{
			/*��ʾ*/
			(new HintWin("ע��ɹ�!"))->Run();
			/*��ת����¼ҳ��*/
			return WIN_LOGIN;
		}
		/*ע��ʧ��*/
		else
		{
			return (new HintWin("ע��ʧ��!"))->Run();;
		}
	}
	return WIN_REFRESH;
}

