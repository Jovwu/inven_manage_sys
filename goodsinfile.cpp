#include "goodsinfile.h"

GoodsInFile::GoodsInFile() :File(GOODS_IN_RECORD)
{
}

bool GoodsInFile::AppendGoodsIn(GoodsIn* goodsin) const
{
	string Content;
	Content.append(goodsin->GetID());
	Content.append(" ");
	Content.append(goodsin->GetName());
	Content.append(" ");
	Content.append(goodsin->GetDate());
	Content.append(" ");
	Content.append(to_string(goodsin->GetCount()));
	Content.append(" ");
	Content.append(goodsin->GetLocID());
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

GoodsIn* GoodsInFile::GetGoodsIn(const string GoodsInString) const
{
	//ÏÈ·Ö¸î×Ö·û´®
	vector<string> Res = Split(GoodsInString);
	vector<string>::iterator It = Res.begin();
	GoodsIn* goodsin = new GoodsIn(*It, *(It + 1), *(It + 2), stoi(*(It + 3)), *(It + 4));
	return goodsin;
}
