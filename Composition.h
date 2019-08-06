#ifndef _COMPOSITION_H_
#define _COMPOSITION_H_

#include "Part.h"

class HashTable;

using pt = pair<Measure*, Measure*>;
using ptNote = pair<MusicSymbol*, MusicSymbol*>;

class Composition
{
private:
	Part * rightHand;
	Part *leftHand; //treba obrisati posle svakog ponovnog pravljenja
	Duration durClk;


public:

	Composition(Part* rh, Part* lh,Duration dur) :rightHand(rh), leftHand(lh),durClk(dur) {};
	void load(string str,HashTable&);


	Part& getRight() const { return *rightHand; }
	Part& getLeft() const { return *leftHand; }
	Duration getDur() const { return durClk; }

	pt nextMeasure();
	pt prevMeasure();
	ptNote nextNote();
	ptNote prevNote();

	void write(ostream&);


	friend ostream& operator<<(ostream& os, Composition& c)
	{
		c.write(os);
		return os;
	}

	Composition& addLeft(Measure* m)
	{
		leftHand->add(m);
		return *this;
	}

	Composition& addRight(Measure* m)
	{
		rightHand->add(m);
		return *this;
	}

	auto rbegin() const { return rightHand->begin(); }
	auto rend() const { return rightHand->end(); }
	auto lbegin() const { return leftHand->begin(); }
	auto lend() const { return leftHand->end(); }
	auto rrbegin() const { return rightHand->rbegin(); }
	auto rrend() const { return rightHand->rend(); }
	void changeOctave(int);
	void changeSharp(string);
	void changeH(string);
	Composition& newOctave(const int&);
	void fillLastMeasure(Measure*, Measure*);
	void addMeasure(Measure**, Measure**);
	pt addBigPause(Measure*,Measure*);
	pt addSmallPause(Measure*,Measure*);
	pt addSimpleNote(Measure*, Measure*, string, int, Duration);
	void addPause(Measure*,Duration d);
	pt addChord(Measure*, Measure*, string, HashTable& h);
	pt addChordNote(Measure*, Measure*, Note*, Note*);
	void chordDec(Note*);
};

#endif // !_COMPOSITION_H_
