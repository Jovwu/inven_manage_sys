#ifndef _MANAGER_MENU_H_
#define _MANAGER_MENU_H_

#include "window.h"
#include "button.h"
#include "checknotefile.h"

class ManagerMenu :public Window
{
public:

	ManagerMenu();
	int Init();//初始化
	int Event(Widget* Obj);
	int Exit();

private:

	Button* GoodsQuery = new Button("商品查询[1]", 32, 11);
	Button* AddGoods = new Button("添加商品[2]", 32, 15);
	Button* GoodsInOut = new Button("商品出入库[3]", 32, 19);
	Button* GoodsOutRecord = new Button("出库记录[4]",72, 11);
	Button* GoodsInRecord = new Button("入库记录[5]", 72, 15);
	Button* CheckRecord = new Button("盘点记录[6]", 72, 19);

};

#endif // !_MANAGER_H_
