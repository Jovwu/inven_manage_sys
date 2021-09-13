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
	bool Sort() const;//将未冲正的内容设置到最前面，其次是冲正中，最后是已冲正

private:
	
};



#endif // !_CHECK_NOTE_H_