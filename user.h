#ifndef _USER_H_
#define _USER_H_
#include <string>
using namespace std;
class User
{
public:

	User(const string ID, const string Name, const string PassWord, const string TYPE);

	string GetID() const;
	string GetName() const;
	string GetPassWord() const;
	string GetTYPE() const;

private:

	string ID;//用户ID
	string Name;//用户名称
	string PassWord;//用户密码
	string TYPE;//用户类型

};
#endif // !_USER_H_

