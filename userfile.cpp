#include "userfile.h"
UserFile::UserFile():File(USER_RECORD)
{
}

bool UserFile::AppendUser(User* user) const
{
	string Content;
	Content.append(user->GetID());
	Content.append(" ");
	Content.append(user->GetName());
	Content.append(" ");
	Content.append(user->GetPassWord());
	Content.append(" ");
	Content.append(user->GetTYPE());
	Content.append(" ");
	if (Append(Content))
	{
		return true;
	}
	else
	{
		return false;
	}
}

User* UserFile::GetUser(const string UserString) const
{
	//ÏÈ·Ö¸î×Ö·û´®
	vector<string> Res = Split(UserString);
	vector<string>::iterator It = Res.begin();
	User* user = new User(*It,*(It+1),*(It+2),*(It+3));
	return user;
}


