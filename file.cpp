#include "file.h"
File::File(const string Path)
{
	this->Path.assign(Path);
}

bool File::SetPath(const string Path)
{
	this->Path.assign(Path);
	return true;
}

vector<string> File::Split(const string String) const
{
	vector<string> Result;
	string Temp;
	int Pos = 0;
	Temp.assign(String);
	for (int Loop = 0; Loop < String.size(); Loop++)
	{
		if (Temp.at(Pos) == ' ')
		{
			Result.push_back(Temp.substr(0, Pos));
			Temp.assign(Temp.substr(++Pos));
			Pos = 0;
			continue;
		}
		Pos++;
	}
	return Result;
}

bool File::ClearFile() const
{
	ifstream ifp;
	ifp.open(this->Path, ios::out|ios::trunc);
	ifp.close();
	return true;
}

bool File::CopyTo(const string Path) const
{
	/*�򿪱��ļ�*/
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	/*��Ŀ���ļ�*/
	ofstream ofp;
	ofp.open(Path, ios::app | ios::out);
	string Temp = "";
	char Buf[1024];
	if (ifp.good() && ofp.good())
	{
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Temp = Buf;
			ofp << Temp << endl;
		}
		ifp.close();
		ofp.close();
		return true;
	}
	else
	{
		ifp.close();
		ofp.close();
		return false;
	}
	return false;
}

string File::Select(int Parameter, const string Target) const
{
	//���ļ�
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	//���ݿո�Ѱ�Ҳ���
	vector<string> Ret;
	vector<string>::iterator It;
	char Buf[1024];
	string Temp = "";
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Temp = Buf;
			Ret = Split(Temp);
			It = Ret.begin() + Parameter - 1;
			if (Target == *It)
			{
				ifp.close();
				return Temp;
			}
		}
	}
	ifp.close();
	return "";
}

int File::Count() const
{
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	if (ifp.good())
	{
		int Count = 0;
		while(ifp.peek() != EOF)
		{
			ifp.ignore(1024,'\n');
			Count++;
		}
		ifp.close();
		return Count;
	}
	ifp.close();
	return 0;
}

string File::SelectByRow(int Row) const
{
	
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	if (ifp.good()) 
	{
		int FileRow = 1;
		string Res;
		char Buf[1024];
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			if (FileRow == Row)
			{
				Res = Buf;
				break;
			}
			FileRow++;
		}
		ifp.close();
		return Res;
	}
	return "";
	
}

vector<string> File::All() const
{
	//���ļ�
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	vector<string> Res;
	string Str;
	char Buf[1024];
	if (ifp.good()) 
	{
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Str = Buf;
			Res.push_back(Str);
		}
		ifp.close();
		return Res;
	}
	ifp.close();
	return Res;
	
}

int File::SelectRow(int Parameter, const string Target) const
{
	//���ļ�
	ifstream ifp;
	ifp.open(this->Path, ios::in);

	//���ݿո�Ѱ�Ҳ���
	vector<string> Ret;
	vector<string>::iterator It;
	char Buf[1024];
	string Temp;
	int Row = 0;
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			Row++;
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Temp = Buf;
			Ret = Split(Temp);
			It = Ret.begin() + Parameter - 1;
			if (Target == *It)
			{
				ifp.close();
				return Row;
			}
		}
	}
	
	ifp.close();
	return 0;
	
}

vector<int> File::SelectRowAll(int Parameter, const string Target) const
{
	//���ļ�
	ifstream ifp;
	ifp.open(this->Path, ios::in);

	//���ݿո�Ѱ�Ҳ���
	vector<string> Ret;
	vector<string>::iterator It;
	vector<int> Res;
	char Buf[1024];
	string Temp;
	int Row = 0;
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			Row++;
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Temp = Buf;
			Ret = Split(Temp);
			It = Ret.begin() + Parameter - 1;
			if (Target == *It)
			{
				Res.push_back(Row);
			}
		}
		ifp.close();
		return Res;
	}
	ifp.close();
	return Res;
	
}

vector<string> File::SeleteAllInvert(int Parameter, const string Target) const
{
	//���ļ�
	ifstream ifp;
	ifp.open(this->Path, ios::in);

	//���ݿո�Ѱ�Ҳ���
	vector<string> Ret;
	vector<string> Result;
	vector<string>::iterator It;
	char Buf[1024];
	string Temp;
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Temp = Buf;
			Ret = Split(Temp);
			It = Ret.begin() + Parameter - 1;
			if (Target != *It)
			{
				Result.push_back(Temp);
			}
		}
		ifp.close();
		return Result;
	}
	ifp.close();
	return Result;
}

string File::SelectSingle(int TargetParameter, const string Target, int SingleParameter) const
{
	//���ҵ�����
	string Content = Select(TargetParameter, Target);
	/*δ�ҵ�*/
	if (Content.empty())
	{
		return "";
	}
	//�ָ�����
	vector<string> Res = Split(Content);
	//�ҵ�����
	string Single = *(Res.begin() + SingleParameter - 1);
	return Single;
}

vector<string> File::SelectAllSingleInvert(int TargetParameter, const string Target, int SingleParameter) const
{
	vector<string> Content = this->SeleteAllInvert(TargetParameter, Target);
	/*���δ�ҵ������ؿ�ֵ*/
	if (Content.empty())
	{
		return Content;
	}
	vector<string>::iterator ContentIt = Content.begin();
	vector<string> Res;
	while (ContentIt != Content.end())
	{
		Res.push_back(*(Split(*ContentIt).begin() + SingleParameter - 1));
		ContentIt++;
	}
	return Res;
}

vector<string> File::SelectAll(int Parameter, const string Target) const
{
	//���ļ�
	ifstream ifp;
	ifp.open(this->Path, ios::in);

	//���ݿո�Ѱ�Ҳ���
	vector<string> Ret;
	vector<string> Result;
	vector<string>::iterator It;
	char Buf[1024];
	string Temp;
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Temp = Buf;
			Ret = Split(Temp);
			It = Ret.begin() + Parameter - 1;
			if (Target == *It)
			{
				Result.push_back(Temp);
			}
		}
		ifp.close();
		return Result;
	}
	ifp.close();
	return Result;
}

string File::SelectFuzzy(int Parameter, const string Target) const
{
	//���ļ�
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	//���ݿո�Ѱ�Ҳ���
	vector<string> Ret;
	vector<string>::iterator It;
	char Buf[1024];
	string Temp;
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			/*ȡһ���������Ա�*/
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Temp = Buf;
			Ret = Split(Temp);
			It = Ret.begin() + Parameter - 1;
			if (strstr((*It).c_str(),Target.c_str()) != NULL)
			{
				ifp.close();
				return Temp;
			}
		}
	}
	ifp.close();
	return "";
	
}

vector<string> File::SelectAllFuzzy(int Parameter, const string Target) const
{
	//���ļ�
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	//�����
	vector<string> Res;
	//���ݿո�Ѱ�Ҳ���
	vector<string> Ret;
	vector<string>::iterator It;
	char Buf[1024];
	string Temp;
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			/*ȡһ���������Ա�*/
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Temp = Buf;
			Ret = Split(Temp);
			It = Ret.begin() + Parameter - 1;
			if (strstr((*It).c_str(), Target.c_str()) != NULL)
			{
				Res.push_back(Temp);
			}
		}
		ifp.close();
		return Res;
	}
	ifp.close();
	return Res;
}

bool File::Modify(int TargetParameter, const string Target, int ContentParameter, const string Content) const
{
	//�ҵ���������һ��
	int Row = SelectRow(TargetParameter, Target);
	//����ԭʼ����
	string Org = Select(TargetParameter, Target);
	/*���û�ҵ�����*/
	if (Org.empty())
	{
		return false;
	}
	//�޸�ԭʼ���ݲ�����
	string Result;
	vector<string> Strs = Split(Org);
	if (Strs.empty())
	{
		return false;
	}
	vector<string>::iterator It = Strs.begin();
	Strs.at(ContentParameter - 1).assign(Content);//�滻

	while (It != Strs.end())
	{
		Result.append(*It);
		Result.append(" ");
		It++;
	}
	//����һ����ʱ�ַ������洢�޸ĺ��ȫ������
	string Temp;
	int Line = 1;
	char Buf[1024];
	//���ļ���ȡ��Ϣ
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			if (Line != Row)
			{
				Temp.append(Buf);
				Temp.append("\n");
			}
			else
			{
				Temp.append(Result);
				Temp.append("\n");
			}
			Line++;
		}
		ifp.close();
	}
	else
	{
		ifp.close();
		return false;
	}
	//д���ļ�
	ofstream ofp;
	ofp.open(this->Path, ios::out);
	if (ofp.good())
	{
		ofp << Temp;
		ofp.close();
		return true;
	}
	else
	{
		ofp.close();
		return false;
	}
}

bool File::Delete(int Parameter, const string Target) const
{
	//�ҵ���������һ��
	int Row = SelectRow(Parameter, Target);
	/*���û�ҵ�����*/
	if (Row == 0)
	{
		return false;
	}
	//����һ����ʱ�ַ������洢�޸ĺ��ȫ������
	string Temp;
	int Line = 1;
	char Buf[1024];
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			if (Line != Row)
			{
				Temp.append(Buf);
				Temp.append("\n");
			}
			else {}
			Line++;
		}
		ifp.close();
	}
	else
	{
		ifp.close();
		return false;
	}
	//д���ļ�
	ofstream ofp;
	ofp.open(this->Path, ios::out);
	if (ofp.good())
	{
		ofp << Temp;
		ofp.close();
		return true;
	}
	else
	{
		ifp.close();
		return false;
	}
}

bool File::DeleteAll(int Parameter, const string Target) const
{
	//�ҵ����ݷֱ�����һ��
	vector<int> Row = SelectRowAll(Parameter, Target);
	/*���û�ҵ�����*/
	if (Row.empty())
	{
		return false;
	}
	vector<int>::iterator It = Row.begin();
	//����һ����ʱ�ַ������洢�޸ĺ��ȫ������
	string Temp;
	int Line = 1;
	char Buf[1024];
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			if (Line != (*It))
			{
				Temp.append(Buf);
				Temp.append("\n");
			}
			else
			{
				It++;
			}
			Line++;
		}
		ifp.close();
	}
	else
	{
		ifp.close();
		return false;
	}
	//д���ļ�
	ofstream ofp;
	ofp.open(this->Path, ios::out);
	if (ofp.good())
	{
		ofp << Temp;
		ofp.close();
		return true;
	}
	else
	{
		ifp.close();
		return false;
	}
}

bool File::Append(const string Content) const
{
	/*�������Ϊ��*/
	if (Content.empty())
	{
		return false;
	}
	ofstream ofp;
	ofp.open(this->Path, ios::app|ios::out);
	if (ofp.good()) 
	{
		ofp << Content << endl;
		ofp.close();
		return true;
	}
	ofp.close();
	return false;
	
}

bool File::AppendFrom(const string FromPath) const

{   /*��Ŀ���ļ�*/
	ifstream ifp;
	ifp.open(FromPath, ios::in);
	/*�򿪱��ļ�*/
	ofstream ofp;
	ofp.open(this->Path, ios::app | ios::out);
	string Temp = "";
	char Buf[1024];
	if (ifp.good() && ofp.good())
	{
		while (ifp.peek() != EOF)
		{
			memset(Buf, 0, 1024);
			ifp.getline(Buf, 1024);
			Temp = Buf;
			ofp << Temp << endl;
		}
		ifp.close();
		ofp.close();
		return true;
	}
	else
	{
		ifp.close();
		ofp.close();
		return false;
	}
	return false;
}
