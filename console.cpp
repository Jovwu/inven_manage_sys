#include "console.h"




void GoToXY(int PositionX, int PositionY)
{
	HANDLE	HOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Point;
	Point.X = PositionX;
	Point.Y = PositionY;
	SetConsoleCursorPosition(HOutput, Point);
}

void HideCursor(int n)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,n };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void ClearArea(int PositionX, int PositionY, int Length)
{
	GoToXY(PositionX, PositionY);
	for (int iCursor = 0; iCursor < Length; iCursor++)
	{
		cout << " ";
	}
}

vector<string> Split(const string String)
{
	vector<string> Result;
	string Temp;
	int Pos = 0;
	Temp.assign(String);
	for (int Loop = 0; Loop < String.size(); Loop++)
	{
		if (Temp.at(Pos) == ' ')
		{
			Result.push_back(Temp.substr(0, Pos));
			Temp.assign(Temp.substr(++Pos));
			Pos = 0;
			continue;
		}
		Pos++;
	}
	return Result;
}

void OrgColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
		FOREGROUND_RED |   // 前景色_红色
		FOREGROUND_GREEN | // 前景色_绿色
		FOREGROUND_BLUE); // 前景色_蓝色
}

void Intensity()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY);
}

