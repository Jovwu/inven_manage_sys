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
	int Init();//��ʼ��
	int Exit();
	int Event(Widget* Obj);

	int LoginButtonEvent();
	int RegButtonEvent();

private:

	//��ɫѡ��
	Label* UserType = new Label("��½��ɫ:", 45, 10);
	Select* UserTypeSelect = new Select(56, 10);
	//�û���
	Label* UserID = new Label("�û�ID:", 45, 13);
	Edit* UserIDEdit = new Edit(53, 13, "NOTCHINESE", USER_ID_MAX);
	//����
	Label* UserPsw = new Label("��  ��:", 45, 15);
	Edit* UserPswEdit = new Edit(53, 15, "PASSWORD", USER_PASSWORD_MAX);
	//��ť
	Button* LoginButton = new Button("��¼", 46, 19);
	Button* RegButton = new Button("ע��", 60, 19);
	
};

class LoginExitBox :public Window
{
public:

	LoginExitBox();
	int Init();
	int Event(Widget* Obj);


private:

	Label* Msg = new Label("ȷ���˳�����", 3, 5);
	Button* OK = new Button("�����˳�", 8, 11);
	Button* NO = new Button("�ֻ���", 25, 11);

};

#endif // !_LOGIN_H_
