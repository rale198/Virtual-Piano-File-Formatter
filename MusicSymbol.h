#ifndef _MUSICSYMBOL_H_
#define _MUSICSYMBOL_H_

#include "Duration.h"

class MusicSymbol
{
public:

protected:

	Duration d;
	bool decomposed;
	int midiValue = 0;

public:

	MusicSymbol(Duration dur=Duration(8, 1), bool dec = false,int m=70) :d(dur), decomposed(dec),midiValue(m) {};
	virtual ~MusicSymbol() {};

	Duration getDuration() const { return d; }
	bool isDecomposed() const { return decomposed; }
	int getMidi() const { return midiValue; }

	virtual void write(ostream& os) const = 0;
	virtual string toString() const = 0;
	friend ostream& operator<<(ostream& os, const MusicSymbol& m)
	{
		m.write(os);
		return os;
	}
};

#endif