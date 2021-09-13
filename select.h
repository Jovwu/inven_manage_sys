#ifndef _SELECT_H_
#define _SELECT_H_
#include "widget.h"
#include "console.h"
#include "keyboard.h"
#include <vector> 
#include <stdarg.h>
#include <cstdarg>
#include <conio.h>
class Select:public Widget
{
public:

	Select(int POSITION_X, int POSITION_Y);
	
	int Load();//�ؼ�����-->��ʾ����Ļ��
	int GetCursor();//��ý���
	int LostCursor();//ʧȥ����
	int OnClick();//�ؼ����ݲ��������Ӧ
	int Refresh();

	int AddOption(const string Option);

private:

	vector<string> Option;


};



#endif // 
