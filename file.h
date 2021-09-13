#ifndef _FILE_H_
#define _FILE_H_
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class File
{
public:

	File(const string Path);
	bool SetPath(const string Path);
	/*ͨ�÷���*/
	vector<string> Split(const string String) const;//���ݿո�ָ��ַ���
	bool ClearFile() const;//����ļ�
	bool CopyTo(const string Path) const;//�����ļ����ݵ�����ָ�����ļ�(����)
	/*��ѯ*/
	int Count() const;//�ļ���Ϣ����������Ϊ��λ
	string SelectByRow(int Row) const;//�����ڵڼ��з�������
	vector<string> All() const;//������Ϣ
	int SelectRow(int Parameter, const string Target) const;//����������ѯ���������ĵ�һ����Ϣ�������ڵڼ���
	vector<int> SelectRowAll(int Parameter, const string Target) const;//����������ѯ����������������Ϣ�������ڷֱ��ڵڼ���
	string SelectSingle(int TargetParameter, const string Target, int SingleParameter) const;//�����������������е�һ��Ԫ��
	vector<string> SelectAllSingleInvert(int TargetParameter, const string Target, int SingleParameter) const;//��ȡ������������������ݵĵ������Լ�
	vector<string> SeleteAllInvert(int Parameter, const string Target) const;//��ȡ�������������������
	/*��ȷ��ѯ*/
	string Select(int Parameter, const string Target) const;//����������ѯ���������ĵ�һ����Ϣ
	vector<string> SelectAll(int Parameter, const string Target) const;//����������ѯ���з�����Ϣ
	/*ģ����ѯ*/
	string SelectFuzzy(int Parameter, const string Target) const;//����������ѯ���������ĵ�һ����Ϣ
	vector<string> SelectAllFuzzy(int Parameter, const string Target) const;//����������ѯ���з�����Ϣ
	/*�޸�*/
	bool Modify(int TargetParameter, const string Target, int ContentParameter, const string Content) const;
	/*ɾ��*/
	bool Delete(int Parameter, const string Target) const;
	bool DeleteAll(int Parameter, const string Target) const;
	/*����*/
	/*����*/
	/*����-->����������Ӿ��巽��*/
	bool Append(const string Content) const;
	bool AppendFrom(const string FromPath) const;//��ָ��·���ļ���ȡ���ݣ���ӵ����ļ���

private:

	string Path;

};

#endif // !_FILE_H_
