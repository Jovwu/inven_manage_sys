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

	string ID;//�û�ID
	string Name;//�û�����
	string PassWord;//�û�����
	string TYPE;//�û�����

};
#endif // !_USER_H_

