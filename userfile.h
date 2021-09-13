#ifndef _USER_FILE_H_
#define _USER_FILE_H_
#include "file.h"
#include "user.h"
#include "config.h"
class UserFile:public File
{
public:

	UserFile();
	bool AppendUser(User* user) const;
	User* GetUser(const string UserString) const;
	
private:
	
};




#endif // !_USER_FILE_H_
