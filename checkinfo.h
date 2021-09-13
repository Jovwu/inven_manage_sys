#ifndef _CHECK_INFO_H_
#define _CHECK_INFO_H_
#include <string>
#include "time.h"
using namespace std;
class CheckInfo
{
public:

	CheckInfo(const string User, const string Goods,int OrgCount, int CheckCount);
	
	string GetUser() const;
	int GetDifference() const;
	string GetGoods() const;
	int GetOrgCount() const;
	int GetCheckCount() const;
	string GetAnalyse() const;

	bool SetDifference();
	bool SetDifference(int Difference);
	bool SetCheckCount(int CheckCount);
	bool SetAnalyse(string Analyse);

private:

	string User;//������Ա
	string Goods;//��Ʒ
	int OrgCount;//��ʼ����
	int CheckCount;//�̵�����
	int Difference;//��������

	string Analyse;//����״̬��0��δ���̣�1���Ѹ���

};

#endif // !_CHECK_H_


