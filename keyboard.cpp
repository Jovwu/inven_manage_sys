#include "keyboard.h"

int GetKey()
{
	char Key = ' ';
	while (1)
	{
		Key = _getch();
		if (Key == ESC_KEY)
		{
			return ESC_KEY;
		}
		else if (Key == ENTER_KEY)
		{
			return ENTER_KEY;
		}
		else if (Key == TAB_KEY)
		{
			return TAB_KEY;
		}
		else if (Key == CTR_KEY)
		{
			switch (_getch())
			{
			case UP_KEY:
				return UP_KEY;
			case LEFT_KEY:
				return LEFT_KEY;
			case RIGHT_KEY:
				return RIGHT_KEY;
			case DOWN_KEY:
				return DOWN_KEY;
			default:
				break;
			}
		}
		else if (Key >48 && Key <=59) 
		{
			return Key;
		}
	}
}


