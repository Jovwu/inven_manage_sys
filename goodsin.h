#ifndef _GOODS_IN_H_
#define _GOODS_IN_H_
#include <string>
using namespace std;
class GoodsIn
{
public:

	GoodsIn(const string ID, const string Name, const string Date, int InCount,string LocID);

	string GetID() const;
	string GetName() const;
	string GetDate() const;
	int GetCount() const;
	string GetLocID() const;

private:

	string ID;//��Ʒ���
	string Name;//��Ʒ����
	string Date;//�������
	int InCount;//�������
	string LocID;//��λ���

};


#endif // !_GOODS_IN_H_
