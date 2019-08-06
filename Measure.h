#ifndef _MEASURE_H_
#define _MEASURE_H_
#include "Chord.h"
#include "GIter.h"
class Measure
{
private:

	Duration dur;
	vector<MusicSymbol*> symbols;
	vector<MusicSymbol*>::iterator ptr;
public:
	Measure(Duration d) :dur(d),ptr(symbols.begin()) {};

	void iterToBegin() { ptr = symbols.begin(); }
	Duration getDur() const { return dur; }
	void setDur(Duration d) { dur = d; }

	auto begin()const { return symbols.begin(); }
	auto end()const { return symbols.end(); }
	MusicSymbol* getNote() const { return *ptr; }
	MusicSymbol* nextNote() { if (ptr == symbols.end()) throw GIter();  ptr++; return *ptr; }
	void nextNote(int) { ptr++; }
	MusicSymbol* prevNote() { if (ptr == symbols.begin()) throw GIter(); ptr--;  return *ptr; }

	friend ostream& operator<<(ostream& os, const Measure& p)
	{
		os << "MEASURE:" << endl;
		for_each(p.begin(), p.end(), [&os](MusicSymbol* m) {os << *m << " "; });
		os << "END OF MEASURE" << endl;
		return os;
	}

	void changeOctave(int oct);
	void changeH(string h);
	void changeSharp(string s);
	string toString() const;
	Measure& add(MusicSymbol* mus);
};
#endif