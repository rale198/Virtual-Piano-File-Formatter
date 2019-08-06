#ifndef _GOCTAVE_H_
#define _GOCTAVE_H_

#include "MusicSymbol.h"

class GOctave {
public:
	friend ostream& operator<<(ostream& os, const GOctave& d)
	{
		os << "*** WRONG OCTAVE FOR THE NOTE, EXPECTED OCTAVE BETWEEN 2 AND 6! ***" << endl;
		return os;
	}
};
#endif