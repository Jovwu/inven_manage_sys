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
	//�ȷָ��ַ���
	vector<string> Res = Split(CheckInfoString);
	vector<string>::iterator It = Res.begin();
	CheckNote* checkNote = new CheckNote(*It);
	checkNote->SetReverse(*(It + 1));
	checkNote->SetExplain(*(It + 2));
	return checkNote;
}

bool CheckNoteFile::Sort() const
{
	/*�����Ż�*/
	/*�µļ�¼*/
	vector<string> NewReverseNote;
	vector<string>::iterator It;
	/*ȡ��δ�����ļ�¼��д��*/
	vector<string> ReverseNoNote = this->SelectAll(2,"δ����");
	It = ReverseNoNote.begin();
	while (It != ReverseNoNote.end())
	{
		NewReverseNote.push_back(*It);
		It++;
	}
	/*ȡ�������еļ�¼��д��*/
	vector<string> ReverseingNote = this->SelectAll(2, "������");
	It = ReverseingNote.begin();
	while (It != ReverseingNote.end())
	{
		NewReverseNote.push_back(*It);
		It++;
	}
	/*ȡ���ѳ����ļ�¼��д��*/
	vector<string> ReverseOkNote = this->SelectAll(2, "�ѳ���");
	It = ReverseOkNote.begin();
	while (It != ReverseOkNote.end())
	{
		NewReverseNote.push_back(*It);
		It++;
	}
	/*���Դ�ļ�*/
	this->ClearFile();
	/*��˳��д��*/
	It = NewReverseNote.begin();
	while (It != NewReverseNote.end())
	{
		this->Append(*It);
		It++;
	}
	return true;
}
