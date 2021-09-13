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

	string ID;//��Ʒ���
	string Name;//��Ʒ����
	string Type;//��Ʒ����
	double Price;//��Ʒ�۸�
	int Count;//��Ʒ���
	string LocID;//��λ���

};


#endif // !_GOODS_H_
