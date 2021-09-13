#ifndef _TABLE_H_
#define _TABLE_H_
#include "widget.h"
#include <vector>
#include <stack>
#include "file.h"
#include "console.h"
#include "td.h"

#define SELECT_ONLY 1
#define SELECT_ALL 2
#define SELECT_FUZZY_ONLY 3
#define SELECT_FUZZY_ALL 4

#define CLICK_NULL 0
#define CLICK_ENTER 1

#define INFO_ORG 0
#define INFO_SELECT 1

class Table:public Widget
{
public:

	Table(const string Value, int POSITION_X, int POSITION_Y);

	int Load();//�ؼ�����-->��ʾ����Ļ��
	int GetCursor();//��ý���
	int LostCursor();//ʧȥ����
	int OnClick();//�ؼ����ݲ��������Ӧ
	int Refresh();//ˢ�¿ؼ�
	bool RefreshHint();//ˢ����ʾ

	int AddTh(const string ThMember);//��ӱ�ͷ-->����"-"
	int SetThW(int ThW);//���ñ����
	int ClickHint();//��������
	int ClearHint();//�������
	bool Update(int Page);//���±������ݵ��ڼ�ҳ

	bool PushState();
	bool PopState();

	/*��ȷ����*/
	bool Select(int Parameter, const string Target);
	bool SelectAllFuzzy(int Parameter, const string Target);//����������ѯ���з�����Ϣ
	/*���ô���ģʽ*/
	bool SetClickMode(int ClickMode);
	/*������������*/
	int SetContentTotal(int ContentTotal);
	/*�����ļ�*/
	int SetFile(File* file);
	/*���÷�ҳ��Ϣ*/
	int SetPaging(int Row);
	/*���ص�����Ϣ*/
	vector<string> GetClickTd() const;
	/*��������*/
	vector<Td*> GetContent() const;
	/*����������ݵ�ָ��·���ļ�*/
	bool ExprotContent(const string Path);
	/*������������*/
	bool InputAllContent();
	/*�����ض�һ��*/
	bool SetLoadAgain();


private:

	//������Ϣ
	vector<string> Th;//��ͷ����
	vector<int> ThW;//��ͷ���->������ͷʱ����
	int Row;//�������-->������ʾ���ı�����,SetPagingʱд��
	int Col;//�������-->�ɱ�ͷ��������������ʱ��ʼ��

	//��ʾ����
	File* file;//����ļ�

	
	int ContentFlag;//��ʾ���ݱ�־λ
	vector<Td*> Content;//��ʾ����
	vector<Td*> SelectContent;//��������

	int ContentTotal;//��������->SetFileʱд��

	//��ʾ��Ϣ�������¿����ݵ���������ǰΪ�ڼ���
	int HintCenterX;//��������X-->�������ʱ��ֵ
	int HintCenterY;//��������Y-->�������ʱ��ֵ

	//�������
	int CursorLine;//��ǰ��ý������
	

	//��ҳ��Ϣ
	int TotalPageNum;//��Ϣ��ҳ��-->����ʱ����Row����
	int PageNum;//��ǰ��Ϣҳ��--->��ʼֵΪ1,����OnClickѡ��+1����-1
	int BrowseYet;//�����ҳ��->�����ж��Ƿ�ȥ�ļ�ȡ������ֱ�Ӵ��ڴ�ȡ,�����浽����

	//������������ʽ
	/*0:�޲�����ֻ�����ҷ�ҳ��
	  1:����ʹ�����¼�ѡ���У���ȷ�ϼ�������ClickTD��������ENTER_KEY
    */
	int ClickMode;
	/*����ģʽ*/
	int SelectMode;
	vector<string> ClickTd;//��ѡ�е�����

	/*״̬ջ*/
	stack<int> StateStack;

	/*���¼������ݱ�־λ*/
	int LoadContentFlag;

};



#endif // !_TABLE_H_
