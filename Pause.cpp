#include "Pause.h"

 string Pause::toString() const  {
	if (Duration(8, 1) >= this->getDuration())
	{
		return "p8";
	}
	return "p4";
}