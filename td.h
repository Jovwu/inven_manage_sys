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

	vector<string> Content;//������ʾ����
	int ClickFlag;//�Ƿ�ѡ��
	int CurrentPageLineNum;//�ڵ�ǰҳ�������
	int FileNum;//�ڵ�ǰ�ļ�������

};

#endif // !_TD_H_
