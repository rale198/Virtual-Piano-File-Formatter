#ifndef _HASH_H_
#define _HASH_H_
#include "Composition.h"

class HashTable
{
private:

	map<string, pair<string, unsigned int> > mapa;

public:

	HashTable & addSymbol(string c, pair<string, unsigned int> opis)
	{
		mapa[c] = opis;
		return *this;
	}


	auto begin() const { return mapa.begin(); }
	auto end() const { return mapa.end(); }



	pair<string, unsigned int> operator[](string s) { return mapa[s]; }


	void parse(string);
	void write(ostream& os) const;
	friend ostream& operator<<(ostream&os, const HashTable& h)
	{
		h.write(os);
		return os;
	}
};

#endif