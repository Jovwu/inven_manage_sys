#include "reg.h"

Reg::Reg():Window("用户注册界面", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int Reg::Init()
{
	/*用户账号为固定值*/
	UserFile* UF = new UserFile();
	UF->Count();
	this->UserIDValue->SetValue(to_string(UF->Count()+1001));
	delete UF;

	this->UserTypeSelect->SetHint("请选择您的注册角色");
	this->UserTypeSelect->AddOption("管理员");
	this->UserTypeSelect->AddOption("盘点员");

	this->UserNameEdit->SetHint("请输入您的名字(仅限中文)");
	this->UserPswEdit->SetHint("请输入您的密码");
	this->RegButton->SetHint("注册一个新账户");
	this->UserPswAgainEdit->SetHint("请再次确认密码");

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
	/*用户名为空*/
	if (this->UserNameEdit->GetValue().empty())
	{
		(new HintWin("用户名不得为空!"))->Run();
		return WIN_CUR_POS_2;
	}
	/*密码为空*/
	else if (this->UserPswEdit->GetValue().empty())
	{
		(new HintWin("用户密码不得为空!"))->Run();
		return WIN_CUR_POS_3;
	}
	/*确认密码为空*/
	else if (this->UserPswAgainEdit->GetValue().empty())
	{
		(new HintWin("请再次输入密码!"))->Run();
		return WIN_CUR_POS_4;
	}
	/*密码两次输入不正确*/
	else if (this->UserPswEdit->GetValue() != this->UserPswAgainEdit->GetValue())
	{
		(new HintWin("前后密码输入不一致!"))->Run();
		this->UserPswAgainEdit->SetValue("");
		return WIN_CUR_POS_4;
	}
	/*满足注册条件*/
	else
	{
		UserFile* UF = new UserFile();
		User* NewUser = new User(
			this->UserIDValue->GetValue(),
			this->UserNameEdit->GetValue(),
			this->UserPswEdit->GetValue(),
			this->UserTypeSelect->GetValue()
		);
		/*判断注册是否成功*/
		/*注册成功*/
		if (UF->AppendUser(NewUser))
		{
			/*提示*/
			(new HintWin("注册成功!"))->Run();
			/*跳转到登录页面*/
			return WIN_LOGIN;
		}
		/*注册失败*/
		else
		{
			return (new HintWin("注册失败!"))->Run();;
		}
	}
	return WIN_REFRESH;
}

