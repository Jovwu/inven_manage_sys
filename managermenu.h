#ifndef _MANAGER_MENU_H_
#define _MANAGER_MENU_H_

#include "window.h"
#include "button.h"
#include "checknotefile.h"

class ManagerMenu :public Window
{
public:

	ManagerMenu();
	int Init();//��ʼ��
	int Event(Widget* Obj);
	int Exit();

private:

	Button* GoodsQuery = new Button("��Ʒ��ѯ[1]", 32, 11);
	Button* AddGoods = new Button("�����Ʒ[2]", 32, 15);
	Button* GoodsInOut = new Button("��Ʒ�����[3]", 32, 19);
	Button* GoodsOutRecord = new Button("�����¼[4]",72, 11);
	Button* GoodsInRecord = new Button("����¼[5]", 72, 15);
	Button* CheckRecord = new Button("�̵��¼[6]", 72, 19);

};

#endif // !_MANAGER_H_
