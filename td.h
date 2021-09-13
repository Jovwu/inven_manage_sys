#ifndef _TD_H_
#define _TD_H_
#include <string>
#include <vector>
#include "console.h"
using namespace std;

class Td
{
public:

	Td(const vector<string> Content, int CurrentPageLineNum, int FileNum);

	vector<string> GetContent() const;
	int GetClickFlag() const;
	int GetCurrentPageLineNum() const;
	int GetFileNum() const;

	bool SetContent(vector<string> Content);
	bool SetClickFlag(int ClickFlag);


private:

	vector<string> Content;//该行显示内容
	int ClickFlag;//是否被选中
	int CurrentPageLineNum;//在当前页面的条数
	int FileNum;//在当前文件的条数

};

#endif // !_TD_H_
