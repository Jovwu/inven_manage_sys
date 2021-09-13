#include"goodsfile.h"

GoodsFile::GoodsFile():File(GOODS_RECORD)
{
}

bool GoodsFile::AppendGoods(Goods* goods) const
{
	string Content;
	Content.append(goods->GetID());
	Content.append(" ");
	Content.append(goods->GetName());
	Content.append(" ");
	Content.append(goods->GetType());
	Content.append(" ");
	Content.append(doubleToString(goods->GetPrice()));
	Content.append(" ");
	Content.append(to_string(goods->GetCount()));
	Content.append(" ");
	Content.append(goods->GetLocID());
	Content.append(" ");
	if (Append(Content))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Goods* GoodsFile::GetGoods(const string GoodsString) const
{
	//ÏÈ·Ö¸î×Ö·û´®
	vector<string> Res = Split(GoodsString);
	vector<string>::iterator It = Res.begin();
	Goods* goods = new Goods(*It, *(It + 1), *(It + 2), stod(*(It + 3)), stoi(*(It + 4)), *(It + 5));
	return goods;
}
