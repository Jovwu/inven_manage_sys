#include "managermenu.h"


ManagerMenu::ManagerMenu() :Window("����Ա������", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int ManagerMenu::Init()
{
	this->GoodsQuery->SetHint("������Ʒ��ѯ����");
	this->AddGoods->SetHint("����µ���Ʒ");
	this->GoodsInOut->SetHint("��Ʒ�ĳ�������");
	this->GoodsInRecord->SetHint("�鿴��Ʒ����¼");
	this->GoodsOutRecord->SetHint("�鿴��Ʒ�����¼");
	this->CheckRecord->SetHint("�鿴�̵��¼,��ѡ��������ߵ�����¼");

	this->Add(this->GoodsQuery);
	this->Add(this->AddGoods);
	this->Add(this->GoodsInOut);
	this->Add(this->GoodsOutRecord);
	this->Add(this->GoodsInRecord);
	this->Add(this->CheckRecord);

	return 0;
}

int ManagerMenu::Exit()
{
	/*����û���¼��Ϣ*/
	USER_TYPE = "���ȵ�¼!";
	USER_NAME = "���ȵ�¼!";
	USER_ID = "NULL!";
	return 0;
}

int ManagerMenu::Event(Widget* Obj)
{
	if (Obj == this->GoodsQuery)
	{
		return WIN_GOODS_QUERY;
	}
	else if (Obj == this->AddGoods) 
	{
		return WIN_ADD_GOODS;
	}
	else if (Obj == this->GoodsInOut)
	{
		return WIN_GOODS_OUT_IN;
	}
	else if (Obj == this->GoodsOutRecord)
	{
		return WIN_GOODS_OUT_RECORD;
	}
	else if (Obj == this->GoodsInRecord)
	{
		return WIN_GOODS_IN_RECORD;
	}
	else if (Obj ==this->CheckRecord)
	{
		CheckNoteFile* CNF = new CheckNoteFile();
		CNF->Sort();
		delete CNF;
		return WIN_CHECK_RECORD;
	}
	return 0;
}
