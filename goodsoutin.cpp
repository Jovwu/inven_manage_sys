#include "goodsoutin.h"


GoodsOutIn::GoodsOutIn() :Window("��Ʒ��������", WIN_POS_X, WIN_POS_Y, WIN_WIDTH, WIN_HEIGHT, "BASE")
{
}

int GoodsOutIn::Init()
{
	this->GoodsIDEdit->SetHint("��������Ʒ���");
	this->Query->SetHint("��ѯ��Ʒ");
	this->CheckCountEdit->SetHint("����������");
	this->Out->SetHint("��Ʒ����");
	this->In->SetHint("��Ʒ���");

	this->Add(this->GoodsID);
	this->Add(this->GoodsIDEdit);
	this->Add(this->Query);
	this->Add(this->GoodsBorder);
	this->Add(this->GoodsName);
	this->Add(this->GoodsNameValue);
	this->Add(this->GoodsType);
	this->Add(this->GoodsTypeValue);
	this->Add(this->GoodsPrice);
	this->Add(this->GoodsPriceValue);
	this->Add(this->GoodsCount);
	this->Add(this->GoodsCountValue);
	this->Add(this->GoodsLocID);
	this->Add(this->GoodsLocIDValue);
	this->Add(this->CheckCount);
	this->Add(this->CheckCountEdit);
	this->Add(this->Out);
	this->Add(this->In);

	return 0;
}

int GoodsOutIn::Event(Widget* Obj)
{
	if (Obj == this->Out) 
	{
		return OutButtonEvent();
	}
	else if (Obj == this->In) 
	{
		return InButtonEvent();
	}
	else if (Obj == this->Query) 
	{
		return QueryButtonEvent();
	}
	return 0;
}

int GoodsOutIn::QueryButtonEvent()
{
	if (this->GoodsIDEdit->GetValue().empty())
	{
		return (new HintWin("��������Ʒ���!"))->Run();
	}
	else
	{
		GoodsFile* GF = new GoodsFile();
		string GoodsStr = GF->Select(1, this->GoodsIDEdit->GetValue());
		if (GoodsStr.empty())
		{
			this->GoodsIDValue.assign("");
			this->GoodsNameValue->SetValue("NULL");
			this->GoodsTypeValue->SetValue("NULL");
			this->GoodsPriceValue->SetValue("NULL");
			this->GoodsCountValue->SetValue("NULL");
			this->GoodsLocIDValue->SetValue("NULL");
			this->GoodsIDEdit->SetValue("");
			(new HintWin("���޴���Ʒ!"))->Run();
			return WIN_CUR_POS_1;
		}
		else
		{
			Goods* goods = GF->GetGoods(GoodsStr);
			this->GoodsIDValue.assign(goods->GetID());
			this->GoodsNameValue->SetValue(goods->GetName());
			this->GoodsTypeValue->SetValue(goods->GetType());
			this->GoodsPriceValue->SetValue(to_string(goods->GetPrice()));
			this->GoodsCountValue->SetValue(to_string(goods->GetCount()));
			this->GoodsLocIDValue->SetValue(goods->GetLocID());
			return WIN_CUR_POS_3;
		}
	}
	return WIN_REFRESH;
}

int GoodsOutIn::OutButtonEvent()
{
	if (this->GoodsIDValue.empty())
	{
		(new HintWin("���Ƚ��в�ѯ!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->CheckCountEdit->GetValue().empty()) 
	{
		(new HintWin("������������!"))->Run();
		return WIN_CUR_POS_3;
	}
	else if (this->CheckCountEdit->GetValue().find('0', 0) == 0)
	{
		this->CheckCountEdit->SetValue("");
		(new HintWin("��Ч���룡"))->Run();
		return WIN_CUR_POS_3;
	}
	else 
	{
		/*�������Ʒ��δ�������߳�����״̬�µļ�¼����ֹ�������*/
		/*�Ȼ�ȡδ�����ͳ����е��̵��¼*/
		CheckNoteFile* CNF = new CheckNoteFile();
		vector<string> CheckInfoID = CNF->SelectAllSingleInvert(2, "�ѳ���", 1);
		if (!CheckInfoID.empty())
		{
			vector<string>::iterator IDIt = CheckInfoID.begin();
			CheckInfoFile* CIF = new CheckInfoFile();
			while (IDIt != CheckInfoID.end())
			{
				CIF->SetPath(CHECK_INFO_RECORD + *IDIt + ".txt");
				/*����ҵ���¼*/
				if (!CIF->Select(2, this->GoodsIDValue).empty())
				{
					(new HintWin("��δ�������̵��¼��"))->Run();
					this->GoodsIDEdit->SetValue("");
					this->CheckCountEdit->SetValue("");
					return WIN_CUR_POS_1;
				}
				IDIt++;
			}
		}else if (stoi(this->GoodsCountValue->GetValue()) < stoi(this->CheckCountEdit->GetValue()))
		{
			(new HintWin("��治��!"))->Run();
			this->CheckCountEdit->SetValue("");
			return WIN_CUR_POS_3;
		}
		/*����ӳ����¼*/
		GoodsOut* GO = new GoodsOut(
			this->GoodsIDValue,
			this->GoodsNameValue->GetValue(),
			DateToString(),
			stoi(this->CheckCountEdit->GetValue()),
			this->GoodsLocIDValue->GetValue()
		);
		GoodsOutFile* GOF = new GoodsOutFile();
		GOF->AppendGoodsOut(GO);
		/*�޸���Ʒ��Ϣ*/
		GoodsFile* GF = new GoodsFile();
		GF->Modify(1,this->GoodsIDValue,5,to_string(stoi(this->GoodsCountValue->GetValue()) - stoi(this->CheckCountEdit->GetValue())));
		/*ˢ��ҳ��ֵ*/
		string GoodsStr = GF->Select(1, this->GoodsIDEdit->GetValue());
		Goods* goods = GF->GetGoods(GoodsStr);
		this->GoodsCountValue->SetValue(to_string(goods->GetCount()));
		this->CheckCountEdit->SetValue("");
		(new HintWin("����ɹ���"))->Run();
		return WIN_CUR_POS_3;
	}
	return WIN_REFRESH;
}

int GoodsOutIn::InButtonEvent()
{
	if (this->GoodsIDValue.empty())
	{
		(new HintWin("���Ƚ��в�ѯ!"))->Run();
		return WIN_CUR_POS_1;
	}
	else if (this->CheckCountEdit->GetValue().empty())
	{
		(new HintWin("������������!"))->Run();
		return WIN_CUR_POS_3;
	}
	else if (this->CheckCountEdit->GetValue().find('0',0) == 0)
	{
		this->CheckCountEdit->SetValue("");
		(new HintWin("��Ч���룡"))->Run();
		return WIN_CUR_POS_3;
	}
	else
	{
		/*�������Ʒ��δ�������߳�����״̬�µļ�¼����ֹ�������*/
		/*�Ȼ�ȡδ�����ͳ����е��̵��¼*/
		CheckNoteFile* CNF = new CheckNoteFile();
		vector<string> CheckInfoID = CNF->SelectAllSingleInvert(2, "�ѳ���", 1);
		if (!CheckInfoID.empty())
		{
			vector<string>::iterator IDIt = CheckInfoID.begin();
			CheckInfoFile* CIF = new CheckInfoFile();
			while (IDIt != CheckInfoID.end())
			{
				CIF->SetPath(CHECK_INFO_RECORD + *IDIt + ".txt");
				/*����ҵ���¼*/
				if (!CIF->Select(2, this->GoodsIDValue).empty())
				{
					(new HintWin("��δ�������̵��¼��"))->Run();
					this->GoodsIDEdit->SetValue("");
					this->CheckCountEdit->SetValue("");
					return WIN_CUR_POS_1;
				}
				IDIt++;
			}
		}
		/*���������¼*/
		GoodsIn* GI = new GoodsIn(
			this->GoodsIDValue,
			this->GoodsNameValue->GetValue(),
			DateToString(),
			stoi(this->CheckCountEdit->GetValue()),
			this->GoodsLocIDValue->GetValue()
		);
		GoodsInFile* GIF = new GoodsInFile();
		GIF->AppendGoodsIn(GI);
		/*�޸���Ʒ��Ϣ*/
		GoodsFile* GF = new GoodsFile();
		GF->Modify(1, this->GoodsIDValue, 5, to_string(stoi(this->GoodsCountValue->GetValue()) + stoi(this->CheckCountEdit->GetValue())));
		/*ˢ��ҳ��ֵ*/
		string GoodsStr = GF->Select(1, this->GoodsIDEdit->GetValue());
		Goods* goods = GF->GetGoods(GoodsStr);
		this->GoodsCountValue->SetValue(to_string(goods->GetCount()));
		this->CheckCountEdit->SetValue("");
		(new HintWin("���ɹ���"))->Run();
		return WIN_CUR_POS_3;
	}
	return WIN_REFRESH;
}
