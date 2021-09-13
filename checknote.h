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
	string Reverse;//冲正状态，0：为冲正，1：冲正中，2：已冲正
	string Explain;

};



#endif // !_CHECK_NOTE_H_
