#ifndef _CHECK_NOTE_H_
#define _CHECK_NOTE_H_
#include <string>

using namespace std;
class CheckNote
{
public:

	CheckNote(const string ID);

	string GetID() const;
	string GetReverse() const;
	string GetExplain() const;

	bool SetExplain(const string Explain);
	bool SetReverse(string Reverse);

private:
	 
	string ID;
	string Reverse;//����״̬��0��Ϊ������1�������У�2���ѳ���
	string Explain;

};



#endif // !_CHECK_NOTE_H_
