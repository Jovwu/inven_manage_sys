#ifndef _GOODS_OUT_H_
#define _GOODS_OUT_H_
#include <string>
using namespace std;
class GoodsOut
{
public:

	GoodsOut(const string ID, const string Name, const string Date, int InCount, string LocID);

	string GetID() const;
	string GetName() const;
	string GetDate() const;
	int GetCount() const;
	string GetLocID() const;

private:

	string ID;//商品编号
	string Name;//商品名称
	string Date;//出库日期
	int InCount;//出库数量
	string LocID;//仓位编号

};


#endif // !_GOODS_OUT_H_