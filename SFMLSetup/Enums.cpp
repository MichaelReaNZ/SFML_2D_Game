#include "Enums.h"

class Enums
{

};

std::string EnumToString(Direction _dir)
{
	{
		switch (_dir)
		{
		case Up:
			return "Up";
			break;
		case Down:
			return "Down";
			break;
		case Left:
			return "Left";
			break;
		case Right:
			return "Right";
			break;
		default:
			return "Error";
			break;
		}

	}
}
