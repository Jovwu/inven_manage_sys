#include "hintwin.h"

HintWin::HintWin(const string Hint):Window("ÌáÊ¾", HINT_BOX_POS_X, HINT_BOX_POS_Y, HINT_BOX_WIDTH, HINT_BOX_HEIGHT, "MSGBOX")
{
	this->VanishFlag = 1;
	this->Hint->SetValue(Hint);
}

int HintWin::Init()
{
	this->Add(this->Hint);
	return 0;
}

int HintWin::Event(Widget* Obj)
{
	return 0;
}


