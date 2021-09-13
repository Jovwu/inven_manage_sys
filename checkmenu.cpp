#include "checkmenu.h"

CheckMenu::CheckMenu():Window("�̵�Ա������", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int CheckMenu::Init()
{
	this->GoodsQuery->SetHint("��ѯ��Ʒ�ı�š����ơ����͡��۸������Ͳ�λ���");
	this->CheckStock->SetHint("�̵�ֿ�����Ʒ������");
	this->CheckRecord->SetHint("�鿴�̵��¼����������Ҫ���и���");
	this->Add(this->GoodsQuery);
	this->Add(this->CheckStock);
	this->Add(this->CheckRecord);
	return 0;
}

int CheckMenu::Exit()
{
	/*����û���¼��Ϣ*/
	USER_TYPE = "���ȵ�¼!";
	USER_NAME = "���ȵ�¼!";
	USER_ID = "NULL!";
	return 0;
}

int CheckMenu::Event(Widget* Obj)
{
	if (Obj == this->GoodsQuery)
	{
		return GoodsQueryButtonEvent();
	}
	else if (Obj == this->CheckStock)
	{
		return CheckStockButtonEvent();
	}
	else if (Obj == this->CheckRecord)
	{
		return CheckRecordButtonEvent();
	}
	return WIN_NO_OPS;
}



int CheckMenu::GoodsQueryButtonEvent()
{
	return WIN_GOODS_QUERY;
}

int CheckMenu::CheckStockButtonEvent()
{
	return WIN_CHECK_STOCK;
}

int CheckMenu::CheckRecordButtonEvent()
{
	return WIN_CHECK_RECORD;
}
