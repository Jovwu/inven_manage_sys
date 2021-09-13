#ifndef _CHECK_INFO_FILE_H_
#define _CHECK_INFO_FILE_H_
#include "file.h"
#include "checkinfo.h"
#include "config.h"
class CheckInfoFile :public File
{
public:

	CheckInfoFile();
	CheckInfoFile(const string Path);
	bool AppendCheckInfo(CheckInfo* CheckInfo) const;
	CheckInfo* GetCheckInfo(const string CheckInfoString) const;


private:
	
};



#endif // !_CHECK_INFO_FILE_H_