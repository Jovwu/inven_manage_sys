#ifndef _LOGIN_H_
#define _LOGIN_H_
#include "window.h"
#include "label.h"
#include "select.h"
#include "edit.h"
#include "button.h"
#include "userfile.h"
#include "hintwin.h"


#define EXIT_CANCEL 11

class Login:public Window
{
public:

	Login();
	int Init();//初始化
	int Exit();
	int Event(Widget* Obj);

	int LoginButtonEvent();
	int RegButtonEvent();

private:

	//角色选择
	Label* UserType = new Label("登陆角色:", 45, 10);
	Select* UserTypeSelect = new Select(56, 10);
	//用户名
	Label* UserID = new Label("用户ID:", 45, 13);
	Edit* UserIDEdit = new Edit(53, 13, "NOTCHINESE", USER_ID_MAX);
	//密码
	Label* UserPsw = new Label("密  码:", 45, 15);
	Edit* UserPswEdit = new Edit(53, 15, "PASSWORD", USER_PASSWORD_MAX);
	//按钮
	Button* LoginButton = new Button("登录", 46, 19);
	Button* RegButton = new Button("注册", 60, 19);
	
};

class LoginExitBox :public Window
{
public:

	LoginExitBox();
	int Init();
	int Event(Widget* Obj);


private:

	Label* Msg = new Label("确认退出程序？", 3, 5);
	Button* OK = new Button("继续退出", 8, 11);
	Button* NO = new Button("手滑了", 25, 11);

};

#endif // !_LOGIN_H_
