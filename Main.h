#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <regex>
#include <fstream>

using namespace std;

class Main {


public :

	void menu() const
	{
		cout << "0. Kraj programa" << endl;
		cout << "1. Ucitavanje podatka o komopiziciji" << endl;
		cout << "2. Ispisivanje kompozicije" << endl;
		cout << "3. Iteriranje kroz kompoziciju" << endl;
		cout << "4. Izmena takta kompozicije" << endl;
		cout << "5. Pomeranje kompozicije" << endl;
		cout << "6. Eksportovanje MIDI file" << endl;
		cout << "7. Eksportovanje MUSICXML file" << endl;
		cout << "8. Eksportovanje BMP file" << endl;
	}

	void iteriranjeTakt() const
	{
		cout << "0. Kraj iteriranja" << endl;
		cout << "1. Prelazak na sledeci takt" << endl;
		cout << "2. Povratak na prethodni takt" << endl;
		cout << "3. Iteriranje kroz note" << endl;

	}

	void iteriranjeNote() const
	{
		cout << "0. Kraj iteriranja" << endl;
		cout  << "1. Prelazak na sledecu notu" << endl;
		cout << "2. Povratak na prethodnu notu" << endl;
		cout << "3. Menjanje oktave" << endl;
		cout << "4. Menjanje visine note" << endl;
		cout << "5. Dodavanje povisilice" << endl;
		cout << "6. Uklanjanje povisilice" << endl;

	}
};

#endif