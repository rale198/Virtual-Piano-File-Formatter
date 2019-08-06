#ifndef _CHORD_H_
#define _CHORD_H_
#include "Pause.h"
class Chord :public Note
{
private:
	vector<Note*> notes;
	Pause* pause;
public:

	Chord(Duration dur = Duration(4, 1), bool dec = false,Pause*p=new Pause(Duration(8,0))) :Note(dur, dec),pause(p) {};

	auto begin() const { return notes.begin(); }
	auto end() const { return notes.end(); }
	auto size() const { return notes.size(); }

	void setPause(Duration d = Duration(4, 1)) { pause = new Pause(d); }
	Chord& add(Note*n) { notes.push_back(n); return *this; }

	Pause getPause() const { return *pause; }
	virtual void write(ostream& os) const override;

	virtual string toString() const override;
};
#endif