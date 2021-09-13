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
	/*通用方法*/
	vector<string> Split(const string String) const;//根据空格分割字符串
	bool ClearFile() const;//清空文件
	bool CopyTo(const string Path) const;//复制文件内容到参数指定的文件(覆盖)
	/*查询*/
	int Count() const;//文件信息数量，以行为单位
	string SelectByRow(int Row) const;//根据在第几行返回数据
	vector<string> All() const;//所有信息
	int SelectRow(int Parameter, const string Target) const;//根据条件查询符合条件的第一条信息，返回在第几行
	vector<int> SelectRowAll(int Parameter, const string Target) const;//根据条件查询符合条件的所有信息，返回在分别在第几行
	string SelectSingle(int TargetParameter, const string Target, int SingleParameter) const;//根据条件返回数据中的一个元素
	vector<string> SelectAllSingleInvert(int TargetParameter, const string Target, int SingleParameter) const;//获取除了条件外的所有内容的单个属性集
	vector<string> SeleteAllInvert(int Parameter, const string Target) const;//获取除了条件外的所有内容
	/*精确查询*/
	string Select(int Parameter, const string Target) const;//根据条件查询符合条件的第一条信息
	vector<string> SelectAll(int Parameter, const string Target) const;//根据条件查询所有符合信息
	/*模糊查询*/
	string SelectFuzzy(int Parameter, const string Target) const;//根据条件查询符合条件的第一条信息
	vector<string> SelectAllFuzzy(int Parameter, const string Target) const;//根据条件查询所有符合信息
	/*修改*/
	bool Modify(int TargetParameter, const string Target, int ContentParameter, const string Content) const;
	/*删除*/
	bool Delete(int Parameter, const string Target) const;
	bool DeleteAll(int Parameter, const string Target) const;
	/*导出*/
	/*导入*/
	/*增加-->由派生类添加具体方法*/
	bool Append(const string Content) const;
	bool AppendFrom(const string FromPath) const;//从指定路径文件读取数据，添加到该文件里

private:

	string Path;

};

#endif // !_FILE_H_
