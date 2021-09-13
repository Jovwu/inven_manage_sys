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
	/*打开本文件*/
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	/*打开目标文件*/
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
	//打开文件
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	//根据空格寻找参数
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
	//打开文件
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
	//打开文件
	ifstream ifp;
	ifp.open(this->Path, ios::in);

	//根据空格寻找参数
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
	//打开文件
	ifstream ifp;
	ifp.open(this->Path, ios::in);

	//根据空格寻找参数
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
	//打开文件
	ifstream ifp;
	ifp.open(this->Path, ios::in);

	//根据空格寻找参数
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
	//先找到数据
	string Content = Select(TargetParameter, Target);
	/*未找到*/
	if (Content.empty())
	{
		return "";
	}
	//分割数据
	vector<string> Res = Split(Content);
	//找到数据
	string Single = *(Res.begin() + SingleParameter - 1);
	return Single;
}

vector<string> File::SelectAllSingleInvert(int TargetParameter, const string Target, int SingleParameter) const
{
	vector<string> Content = this->SeleteAllInvert(TargetParameter, Target);
	/*如果未找到，返回空值*/
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
	//打开文件
	ifstream ifp;
	ifp.open(this->Path, ios::in);

	//根据空格寻找参数
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
	//打开文件
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	//根据空格寻找参数
	vector<string> Ret;
	vector<string>::iterator It;
	char Buf[1024];
	string Temp;
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			/*取一条数据做对比*/
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
	//打开文件
	ifstream ifp;
	ifp.open(this->Path, ios::in);
	//结果集
	vector<string> Res;
	//根据空格寻找参数
	vector<string> Ret;
	vector<string>::iterator It;
	char Buf[1024];
	string Temp;
	if (ifp.good())
	{
		while (ifp.peek() != EOF)
		{
			/*取一条数据做对比*/
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
	//找到数据在哪一行
	int Row = SelectRow(TargetParameter, Target);
	//返回原始数据
	string Org = Select(TargetParameter, Target);
	/*如果没找到数据*/
	if (Org.empty())
	{
		return false;
	}
	//修改原始数据并拷贝
	string Result;
	vector<string> Strs = Split(Org);
	if (Strs.empty())
	{
		return false;
	}
	vector<string>::iterator It = Strs.begin();
	Strs.at(ContentParameter - 1).assign(Content);//替换

	while (It != Strs.end())
	{
		Result.append(*It);
		Result.append(" ");
		It++;
	}
	//创建一个临时字符串来存储修改后的全部内容
	string Temp;
	int Line = 1;
	char Buf[1024];
	//从文件读取信息
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
	//写入文件
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
	//找到数据在哪一行
	int Row = SelectRow(Parameter, Target);
	/*如果没找到数据*/
	if (Row == 0)
	{
		return false;
	}
	//创建一个临时字符串来存储修改后的全部内容
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
	//写入文件
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
	//找到数据分别在哪一行
	vector<int> Row = SelectRowAll(Parameter, Target);
	/*如果没找到数据*/
	if (Row.empty())
	{
		return false;
	}
	vector<int>::iterator It = Row.begin();
	//创建一个临时字符串来存储修改后的全部内容
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
	//写入文件
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
	/*如果数据为空*/
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

{   /*打开目标文件*/
	ifstream ifp;
	ifp.open(FromPath, ios::in);
	/*打开本文件*/
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
