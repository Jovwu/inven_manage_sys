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

	string User;//操作人员
	string Goods;//商品
	int OrgCount;//初始数量
	int CheckCount;//盘点数量
	int Difference;//差异数量

	string Analyse;//复盘状态，0：未复盘，1：已复盘

};

#endif // !_CHECK_H_


