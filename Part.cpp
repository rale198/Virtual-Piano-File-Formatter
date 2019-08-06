#include "Part.h"

Measure* Part::nextMeasure() {
	if (ptr == clocks.end()) throw GIter();
	ptr++;
	return *ptr;
}

Measure* Part::prevMeasure() {
	if (ptr == clocks.begin()) throw GIter();
	ptr--;
	return *ptr;
}

void Part::prevMeasure(int i)
{
	if (ptr == clocks.begin()) throw GIter();
	ptr--;
}
void Part::nextMeasure(int i)
{
		if (ptr == clocks.end()) throw GIter();
	ptr++;
}

MusicSymbol* Part::nextNote() {
	Measure* m = *ptr;
	return m->nextNote();
}

MusicSymbol* Part::prevNote() {
	Measure* m = *ptr;
	return m->prevNote();
}

Part& Part::add(Measure* m) {

	clocks.push_back(m);
	return *this;
}