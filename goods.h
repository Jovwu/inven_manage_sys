#ifndef _GOODS_H_
#define _GOODS_H_
#include <string>
using namespace std;
class Goods
{
public:

	Goods(const string ID, const string Name, const string Type, double Price, int Count, string LocID);

	int SetPrice(double Price);
	int SetCount(int Count);

	string GetID() const;
	string GetName() const;
	string GetType() const;
	double GetPrice() const;
	int GetCount() const;
	string GetLocID() const;

private:

	string ID;//商品编号
	string Name;//商品名称
	string Type;//商品类型
	double Price;//商品价格
	int Count;//商品库存
	string LocID;//仓位编号

};


#endif // !_GOODS_H_
