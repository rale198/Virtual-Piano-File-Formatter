#ifndef _PART_H_
#define _PATH_H_

#include "Measure.h"
class Part {
private:
	vector<Measure*> clocks;
	vector<Measure*>::iterator ptr;
public:

	auto begin() const { return clocks.begin(); }
	auto rbegin() const { return clocks.rbegin(); }
	auto rend() const { return clocks.rend(); }
	auto end() const { return clocks.end(); }

	Measure* getIter() const { return *ptr; }

	Measure* nextMeasure();
	Measure* prevMeasure();
	void nextMeasure(int);
	void prevMeasure(int);

	MusicSymbol* nextNote();
	MusicSymbol* prevNote();

	Part& add(Measure* m);

	friend ostream& operator<<(ostream& os, const Part& p)
	{
		for_each(p.begin(), p.end(), [&os](Measure* m) {os << *m << endl; });
		return os;
	}

	void changeOctave(int oct)
	{
		Measure* p = *ptr;
		p->changeOctave(oct);
	}

	void changeH(string h)
	{
		Measure* p = *ptr;
		p->changeH(h);
	}

	void changeSharp(string s)
	{
		Measure *p = *ptr;
		p->changeSharp(s);
	}

	void iterToBegin() { ptr = this->clocks.begin(); }
};
#endif
