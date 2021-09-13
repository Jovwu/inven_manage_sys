#include "app.h"
#include "config.h"
#include "login.h"
#include "reg.h"
#include "checkmenu.h"
#include "goodsquery.h"
#include "checkstock.h"
#include "checkrecord.h"
#include "checkrecordsingle.h"
#include "addgoods.h"
#include "goodsoutin.h"
#include "goodsoutrecord.h"
#include "goodsinrecord.h"
#include "managermenu.h"
void App() 
{
	int CurWin = WIN_LOGIN;
	while (1)
	{
		switch (CurWin)
		{
		case WIN_LOGIN:
			CurWin = (new Login())->Run();
			break;
		case WIN_REG:
			CurWin = (new Reg())->Run();
			break;
		case WIN_CHECK_MENU:
			CurWin = (new CheckMenu())->Run();
			break;
		case WIN_ADMIN_MENU:
			CurWin = (new ManagerMenu())->Run();
			break;
		case WIN_GOODS_QUERY:
			CurWin = (new GoodsQuery())->Run();
			break;
		case WIN_CHECK_STOCK:
			CurWin = (new CheckStock())->Run();
			break;
		case WIN_CHECK_RECORD:
			CurWin = (new CheckRecord())->Run();
			break;
		case WIN_CHECK_RECORD_SINGLE:
			CurWin = (new CheckRecordSingle())->Run();
			break;
		case WIN_ADD_GOODS:
			CurWin = (new AddGoods())->Run();
			break;
		case WIN_GOODS_OUT_IN:
			CurWin = (new GoodsOutIn())->Run();
			break;
		case WIN_GOODS_OUT_RECORD:
			CurWin = (new GoodsOutRecord())->Run();
			break;
		case WIN_GOODS_IN_RECORD:
			CurWin = (new GoodsInRecord())->Run();
			break;
		}
		if (CurWin == ESC_KEY)
		{
			/*如果此时只剩一个页面，退出程序*/
			if (Windows.size() == 1)
			{
				system("cls");
				exit(0);
			}
			/*清除界面*/
			delete Windows.top();
			Windows.pop();
			CurWin = Windows.top()->Run();
		}
	}
}