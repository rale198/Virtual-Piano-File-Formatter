#ifndef _DENOM_H_
#define _DENOM_H_

#include "Main.h"
class GDenominator
{

public:

	friend ostream& operator<<(ostream& os, const GDenominator& d)
	{
		os << "*** WRONG NUMBER IN DENOMINATOR, EXPECTED 4 OR 8 ONLY! ***" << endl;
		return os;
	
	}
};

#endif