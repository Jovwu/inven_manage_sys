#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <vector>
#include <stack>
#include "widget.h"
#include "console.h"
#include "config.h"
#include "time.h"
#include "file.h"
using namespace std;

class Window
{
public:

	Window(const string Title,int PositionX, int PositionY,int Width,int Height,const string Type);

	virtual int Init() = 0;//��ʼ��
	virtual int Event(Widget* Obj) = 0;//�ؼ��¼�
	virtual int Exit();//ҳ���˳�
	int Add(Widget* widget);//�ؼ����
	int Load();//ҳ�����
	int Run();//����
	int Refresh();//ˢ�½���
	int ShowHint(const string Hint);//��ʾ�ؼ���ʾ��Ϣ
	
protected:

	//������Ϣ
	int Width;//���
	int Height;//�߶�
	int PositionX;//���Ͻ�X
	int PositionY;//���Ͻ�Y
	string Type;//��������
	//��ʾ��Ϣ
	string Title;//����
    //�ؼ�
	vector<Widget*> WidgetVec;
	stack<Window*> MsgBoxSt;
	//�Զ���ʧ��־λ-->������ʾ��
	int VanishFlag;

};



#endif // !_WINDOW_H_
