#ifndef _REG_H_
#define _REG_H_
#include "window.h"
#include "label.h"
#include "select.h"
#include "edit.h"
#include "button.h"
#include "userfile.h"
#include "hintwin.h"
class Reg :public Window
{
public:

	Reg();
	int Init();//初始化
	int Event(Widget* Obj);


	int RegButtonEvent();//注册按钮事件


private:

	//角色选择
	Label* UserType = new Label("角色类型:", 45, 11);
	Select* UserTypeSelect = new Select(56, 11);
	//用户ID
	Label* UserID = new Label("用户ID:", 45, 13);
	Label* UserIDValue = new Label("此处为固定值", 53, 13);
	//用户名
	Label* UserName = new Label("用户名:", 45, 15);
	Edit* UserNameEdit = new Edit(53, 15, "ONLYCHINESE", USER_NAME_MAX);
	//密码
	Label* UserPsw = new Label("密  码:", 45, 17);
	Edit* UserPswEdit = new Edit(53, 17, "PASSWORD", USER_PASSWORD_MAX);
	//确认密码
	Label* UserPswAgain = new Label("确认密码:", 45, 19);
	Edit* UserPswAgainEdit = new Edit(55, 19, "PASSWORD", USER_PASSWORD_MAX);
	//按钮
	Button* RegButton = new Button("注册", 53, 22);

};





#endif // !_REG_H_
