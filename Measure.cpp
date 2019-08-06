#include "Measure.h"

Measure& Measure::add(MusicSymbol* mus)
{
	symbols.push_back(mus);
	ptr = symbols.begin();
	return *this;
}

void Measure::changeOctave(int oct) {
	MusicSymbol* p = *ptr;
	if (typeid(*p) == typeid(Note) || typeid(*p) == typeid(Chord))
		if (((Note*)p)->getOctave() + oct <= 6 && ((Note*)p)->getOctave() + oct >= 2)
			((Note*)p)->setOctave(((Note*)p)->getOctave() + oct);
	cout << *p << endl;
}

void Measure::changeH(string h)
{
	MusicSymbol* p = *ptr;
	if (typeid(*p) == typeid(Note) || typeid(*p) == typeid(Chord))
		((Note*)p)->setH(h);
	cout << *p << endl;
}

void Measure::changeSharp(string s)
{
	MusicSymbol* p = *ptr;
	if (typeid(*p) == typeid(Note) || typeid(*p) == typeid(Chord))
		((Note*)p)->setSharp(s);
	cout << *p << endl;
}

string Measure::toString() const
{
	string str = "|";
	for_each(begin(), end(), [&str](MusicSymbol* m) {
		str += m->toString() += " ";
	});

	return str;
}