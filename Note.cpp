#include "Note.h"

string Note::toString() const 
{
	string ret;
	if (Duration(8, 1) >= this->getDuration())
	{
		ret += string(1, tolower(height[0])) + sharp;
		ret += to_string(this->getOctave());
	}
	else ret += getNote();

	if (isDecomposed()) ret += "*";
	return ret;
}