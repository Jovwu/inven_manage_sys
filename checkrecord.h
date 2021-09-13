#ifndef _CHECK_RECORD_H_
#define _CHECK_RECORD_H_
#include "window.h"
#include "button.h"
#include "label.h"
#include "table.h"
#include "checkinfofile.h"
#include "hintwin.h"
#include "checknotefile.h"
class CheckRecord :public Window
{
public:

	CheckRecord();
	int Init();//初始化
	int Event(Widget* Obj);

	int CheckTableEvent();

private:

	
	Table* CheckTable = new Table("盘点信息表", 40, 10);

};



#endif // !_CHECK_MENU_H_
