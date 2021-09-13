#include "checknotefile.h"
CheckNoteFile::CheckNoteFile():File(CHECK_NOTE_RECORD)
{
}

bool CheckNoteFile::AppendCheckNote(CheckNote* CheckNote) const
{
	string Content;
	Content.append(CheckNote->GetID());
	Content.append(" ");
	Content.append(CheckNote->GetReverse());
	Content.append(" ");
	Content.append(CheckNote->GetExplain());
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

CheckNote* CheckNoteFile::GetCheckNote(const string CheckInfoString) const
{
	//先分割字符串
	vector<string> Res = Split(CheckInfoString);
	vector<string>::iterator It = Res.begin();
	CheckNote* checkNote = new CheckNote(*It);
	checkNote->SetReverse(*(It + 1));
	checkNote->SetExplain(*(It + 2));
	return checkNote;
}

bool CheckNoteFile::Sort() const
{
	/*可作优化*/
	/*新的记录*/
	vector<string> NewReverseNote;
	vector<string>::iterator It;
	/*取出未冲正的记录并写入*/
	vector<string> ReverseNoNote = this->SelectAll(2,"未冲正");
	It = ReverseNoNote.begin();
	while (It != ReverseNoNote.end())
	{
		NewReverseNote.push_back(*It);
		It++;
	}
	/*取出冲正中的记录并写入*/
	vector<string> ReverseingNote = this->SelectAll(2, "冲正中");
	It = ReverseingNote.begin();
	while (It != ReverseingNote.end())
	{
		NewReverseNote.push_back(*It);
		It++;
	}
	/*取出已冲正的记录并写入*/
	vector<string> ReverseOkNote = this->SelectAll(2, "已冲正");
	It = ReverseOkNote.begin();
	while (It != ReverseOkNote.end())
	{
		NewReverseNote.push_back(*It);
		It++;
	}
	/*清空源文件*/
	this->ClearFile();
	/*按顺序写入*/
	It = NewReverseNote.begin();
	while (It != NewReverseNote.end())
	{
		this->Append(*It);
		It++;
	}
	return true;
}
