#include "goodsquery.h"
GoodsQuery::GoodsQuery():Window("��Ʒ��ѯ����", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{

}
int GoodsQuery::Init()
{
	this->GoodsInfo->SetFile(new GoodsFile());
	this->GoodsInfo->SetPaging(3);
	this->GoodsInfo->SetClickMode(0);

	this->GoodsInfo->AddTh("��Ʒ���");
	this->GoodsInfo->AddTh("��Ʒ����");
	this->GoodsInfo->AddTh("��Ʒ����");
	this->GoodsInfo->AddTh("��Ʒ�۸�");
	this->GoodsInfo->AddTh("�������");
	this->GoodsInfo->AddTh("��λ���");


	this->GoodsIDEdit->SetHint("��������Ʒ��ID");
	this->Query->SetHint("��ȷ��ѯ��Ʒ");
	this->QueryFuzzy->SetHint("ģ����ѯ��Ʒ");
	this->GoodsInfo->SetHint("��Ʒ��Ϣ��");
	this->Export->SetHint("����������ݵ��ⲿ�ļ�");


	this->Add(this->GoodsID);
	this->Add(this->GoodsIDEdit);
	this->Add(this->Query);
	this->Add(this->QueryFuzzy);
	this->Add(this->GoodsInfo);
	this->Add(this->Export);

	return 0;
}

int GoodsQuery::Event(Widget* Obj)
{
	if (Obj == this->Query)
	{
		return QueryButtonEvent();
	}
	else if (Obj == this->QueryFuzzy)
	{
		return QueryFuzzyButtonEvent();
	}
	else if (Obj == this->Export) 
	{
		return ExportButtonEvent();
	}
	return 0;
}

int GoodsQuery::QueryButtonEvent()
{
	if (this->GoodsIDEdit->GetValue().empty()) 
	{
		(new HintWin("��������Ʒ���!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->GoodsInfo->Select(1, this->GoodsIDEdit->GetValue()) == false)
	{
		if (USER_TYPE == "����Ա") 
		{
			/*��ѯ���Ƿ���Ҫ�������Ʒ*/
			int Ret = (new ChoiceBox())->Run();
			if (Ret == CHOICE_ADD)
			{
				this->GoodsInfo->SetLoadAgain();
				/*����Ʒ���ҳ��*/
				return WIN_ADD_GOODS;
			}
			else if (Ret == CHOICE_CANCEL)
			{
				this->GoodsIDEdit->SetValue("");
				return WIN_CUR_POS_1;
			}
			return WIN_REFRESH;
		}
		else if (USER_TYPE == "�̵�Ա") 
		{
			(new HintWin("�Ҳ�������Ʒ!"))->Run();
			this->GoodsIDEdit->SetValue("");
			return WIN_CUR_POS_1;
		}
	}
	/*�ҵ���*/
	return WIN_NO_OPS;
}

int GoodsQuery::QueryFuzzyButtonEvent()
{
	if (this->GoodsIDEdit->GetValue().empty())
	{
		(new HintWin("��������Ʒ���!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->GoodsInfo->SelectAllFuzzy(1, this->GoodsIDEdit->GetValue()) == false)
	{
		(new HintWin("�޲�ѯ���!"))->Run();
		this->GoodsIDEdit->SetValue("");
		return WIN_CUR_POS_1;
	}
	/*�ҵ����*/
	else 
	{
		return WIN_CUR_POS_4;
	}
	return 0;
}

int GoodsQuery::ExportButtonEvent()
{
	(new HintWin("���ڵ���..."))->Run();
	this->GoodsInfo->ExprotContent(EXPORT_FILE_PATH + DateToString() + "GI" + ".txt");
	return (new HintWin("�����ɹ�"))->Run();
}

ChoiceBox::ChoiceBox() :Window("��ʾ", CTR_BOX_POS_X, CTR_BOX_POS_Y, CTR_BOX_WIDTH, CTR_BOX_HEIGHT, "MSGBOX")
{
}

int ChoiceBox::Init()
{
	this->Add(this->Msg);
	this->Add(this->AddGoods);
	this->Add(this->Cancel);
	return 0;
}

int ChoiceBox::Event(Widget* Obj)
{
	if (Obj == this->AddGoods)
	{
		return CHOICE_ADD;
	}
	else if (Obj == this->Cancel)
	{
		return CHOICE_CANCEL;
	}
	return 0;
}
