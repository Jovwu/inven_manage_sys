#ifndef _CHECK_NOTE_FILE_H_
#define _CHECK_NOTE_FILE_H_
#include "file.h"
#include "checknote.h"
#include "config.h"
class CheckNoteFile :public File
{
public:

	CheckNoteFile();
	bool AppendCheckNote(CheckNote* CheckNote) const;
	CheckNote* GetCheckNote(const string CheckInfoString) const;
	bool Sort() const;//��δ�������������õ���ǰ�棬����ǳ����У�������ѳ���

private:
	
};



#endif // !_CHECK_NOTE_H_