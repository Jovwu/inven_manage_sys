#include "goodsoutfile.h"

GoodsOutFile::GoodsOutFile() :File(GOODS_OUT_RECORD)
{
}

bool GoodsOutFile::AppendGoodsOut(GoodsOut* goodsout) const
{
	string Content;
	Content.append(goodsout->GetID());
	Content.append(" ");
	Content.append(goodsout->GetName());
	Content.append(" ");
	Content.append(goodsout->GetDate());
	Content.append(" ");
	Content.append(to_string(goodsout->GetCount()));
	Content.append(" ");
	Content.append(goodsout->GetLocID());
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

GoodsOut* GoodsOutFile::GetGoodsOut(const string GoodsInString) const
{
	//ÏÈ·Ö¸î×Ö·û´®
	vector<string> Res = Split(GoodsInString);
	vector<string>::iterator It = Res.begin();
	GoodsOut* goodsout = new GoodsOut(*It, *(It + 1), *(It + 2), stoi(*(It + 3)), *(It + 4));
	return goodsout;
}
