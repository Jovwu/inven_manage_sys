#include "login.h"

Login::Login():Window("用户登录界面",WIN_POS_X,WIN_POS_Y,WIN_WIDTH,WIN_HEIGHT,"BASE")
{
}

int Login::Init()
{
	this->UserTypeSelect->SetHint("请选择您的角色类型");
	this->UserTypeSelect->AddOption("管理员");
	this->UserTypeSelect->AddOption("盘点员");

	this->UserIDEdit->SetHint("请输入您的账号");
	this->UserPswEdit->SetHint("请输入您的密码");
	this->LoginButton->SetHint("登录到角色相关页面进行操作");
	this->RegButton->SetHint("注册一个新账户");

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
		/*确认退出*/
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
	/*用户名为空*/
	if (this->UserIDEdit->GetValue().empty()) 
	{
		(new HintWin("用户ID不得为空!"))->Run();
		return WIN_CUR_POS_2;
	}
	/*密码为空*/
	else if (this->UserPswEdit->GetValue().empty())
	{
		(new HintWin("用户密码不得为空!"))->Run();
		return WIN_CUR_POS_3;
	}
	/*用户不存在*/
	else if (UF->Select(1,this->UserIDEdit->GetValue()).empty())
	{
		(new HintWin("用户不存在!"))->Run();
		this->UserIDEdit->SetValue("");
		this->UserPswEdit->SetValue("");
		return WIN_CUR_POS_2;
	}
	/*密码不正确*/
	else if (UF->SelectSingle(1, this->UserIDEdit->GetValue(),3) != this->UserPswEdit->GetValue())
	{
		this->UserPswEdit->SetValue("");
		(new HintWin("用户密码不正确!"))->Run();
		return WIN_CUR_POS_3;
	}
	/*角色验证*/
	else 
	{
		/*盘点员*/
		if (this->UserTypeSelect->GetValue() == "盘点员")
		{
			/*进行盘点员身份认证*/
			if (UF->SelectSingle(1, this->UserIDEdit->GetValue(), 4) != "盘点员")
			{
				(new HintWin("您不是盘点员!"))->Run();
				return WIN_CUR_POS_1;
			}
			/*修改config.h*/
			USER_ID = this->UserIDEdit->GetValue();
			USER_NAME = UF->SelectSingle(1, this->UserIDEdit->GetValue(), 2);
			USER_TYPE = this->UserTypeSelect->GetValue();
			/*清空页面值*/
			this->UserIDEdit->SetValue("");
			this->UserPswEdit->SetValue("");
			/*跳转到盘点员界面*/
			return WIN_CHECK_MENU;
		}
		/*管理员*/
		else if (this->UserTypeSelect->GetValue() == "管理员")
		{
			/*进行管理员身份认证*/
			if (UF->SelectSingle(1, this->UserIDEdit->GetValue(), 4) != "管理员")
			{
				(new HintWin("您不是管理员!"))->Run();
				return WIN_CUR_POS_1;
			}
			/*修改config.h*/
			USER_ID = this->UserIDEdit->GetValue();
			USER_NAME = UF->SelectSingle(1, this->UserIDEdit->GetValue(), 2);
			USER_TYPE = this->UserTypeSelect->GetValue();
			/*清空页面值*/
			this->UserIDEdit->SetValue("");
			this->UserPswEdit->SetValue("");
			/*跳转到管理员界面*/
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
LoginExitBox::LoginExitBox() :Window("提示", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
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
		/*空操作*//*需修改*/
		return EXIT_CANCEL;
	}
	return 0;

}