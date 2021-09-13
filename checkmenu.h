#ifndef _CHECK_MENU_H_
#define _CHECK_MENU_H_
#include "window.h"
#include "button.h"

class CheckMenu :public Window
{
public:

	CheckMenu();
	int Init();//��ʼ��
	int Exit();
	int Event(Widget* Obj);


	int GoodsQueryButtonEvent();
	int CheckStockButtonEvent();
	int CheckRecordButtonEvent();


private:

	Button* GoodsQuery = new Button("��Ʒ��ѯ[1]", 22, 15);
	Button* CheckStock = new Button("�½��̵�[2]", 52, 15);
	Button* CheckRecord = new Button("�̵��¼[3]", 82, 15);

};

#endif // !_CHECK_MENU_H_
