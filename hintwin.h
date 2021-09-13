#ifndef _HINT_WIN_
#define _HINT_WIN_
#include "window.h"
#include"label.h"
class HintWin:public Window
{
public:

	HintWin(const string Hint);
	int Init();//≥ı ºªØ
	int Event(Widget* Obj);


private:

	Label* Hint = new Label("Label:", 4, 4);
};

#endif // !_HINT_WIN_
