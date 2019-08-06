#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "Note.h"

class Pause :public MusicSymbol
{

public:

	Pause(Duration d = Duration(8, 1), bool dec = false) :MusicSymbol(d, dec) {};

	virtual void write(ostream& os) const override {
		os << "P"<<d;
	}
	virtual string toString() const override;
};

#endif