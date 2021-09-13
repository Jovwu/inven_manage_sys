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
	int Init();//��ʼ��
	int Event(Widget* Obj);


	int RegButtonEvent();//ע�ᰴť�¼�


private:

	//��ɫѡ��
	Label* UserType = new Label("��ɫ����:", 45, 11);
	Select* UserTypeSelect = new Select(56, 11);
	//�û�ID
	Label* UserID = new Label("�û�ID:", 45, 13);
	Label* UserIDValue = new Label("�˴�Ϊ�̶�ֵ", 53, 13);
	//�û���
	Label* UserName = new Label("�û���:", 45, 15);
	Edit* UserNameEdit = new Edit(53, 15, "ONLYCHINESE", USER_NAME_MAX);
	//����
	Label* UserPsw = new Label("��  ��:", 45, 17);
	Edit* UserPswEdit = new Edit(53, 17, "PASSWORD", USER_PASSWORD_MAX);
	//ȷ������
	Label* UserPswAgain = new Label("ȷ������:", 45, 19);
	Edit* UserPswAgainEdit = new Edit(55, 19, "PASSWORD", USER_PASSWORD_MAX);
	//��ť
	Button* RegButton = new Button("ע��", 53, 22);

};





#endif // !_REG_H_
