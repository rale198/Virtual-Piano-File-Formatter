#ifndef _MUSICSY_H_
#define _MUSICSY_H_

#include "GOctave.h"

class Note:public MusicSymbol
{
private:
	string sharp;
	string height;
	int octave;


public:

	Note(Duration dur=Duration(8,1), bool dec=false, string sh="", string hh="C", int oct=4,int m=70) :MusicSymbol(dur, dec,m), sharp(sh), height(hh), octave(oct)
	{
		if (octave < 2 || octave>6) throw GOctave();
	}
	virtual ~Note() {};

	virtual void write(ostream& os) const override {
		string s = (decomposed == true) ? "D" : "";
		os << getNote()<<d<<s;
	}
	bool isSharp() const { return sharp=="#"; }
	void setSharp(string s="#") {  sharp = s; }
	string getNote() const { string s = height + sharp; s += to_string(octave); return s; }
	int getOctave() const { return octave; }
	string getHeight() const { return this->height; }

	void setDecomposed() { decomposed = true; }
	void setDur(Duration dur) { d = dur; }
	void setOctave(int oct) { octave = oct;}
	void setH(string h) { height = h; }

	virtual string toString() const override;
};

#endif