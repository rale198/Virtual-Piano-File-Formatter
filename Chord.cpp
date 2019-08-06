#include "Chord.h"

void Chord::write(ostream& os) const
{
		os << "Chord:[";
		for_each(begin(), end(), [&os](Note* t) {t->write(os); });
		char c;
		if (isDecomposed()) c = 'D';
		else c = ' ';
		os << "]" << c;


}

string Chord::toString() const
{
		string ret = "";
		if(this->size()>0)
		for_each(this->begin(), this->end(), [this,&ret](Note* n) {
			ret += n->toString();

		});
		else ret += this->pause->toString();

		if (this->isDecomposed() == true) ret += "*";
		return ret;
}