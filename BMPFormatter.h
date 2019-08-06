#ifndef _BMPF_H_
#define _BMPF_H_
#include "Formater.h"

class BmpFormatter :public Formater
{

private:

	enum Color { RED = 0, GREEN, BLUE };
	map<string, int*> mapa;
	int weight, numPx;
	int height = numPx / weight + 1;
	vector<string> data;

	void fillPx(ofstream&);
	void filltheHashMap();
	void generateBMP(ofstream&);
	void generateMatrix();

	void setPause(string&);
	void fillChords(string&, MusicSymbol*, MusicSymbol*);
	int* fillNote(string&, MusicSymbol*);
	inline int x2(int x4) { return x4 - x4 / 8 * 6; }
	inline int x3(int x4) { return x4 - x4 / 8 * 3; }
	inline int x4(int x) { return x; }
	inline int x5(int x4) { return x4 + (255 - x4) / 8 * 3; }
	inline int x6(int x4) { return x4 + (255 - x4) / 8 * 6; }

	void calc_the_field(string&, MusicSymbol*, MusicSymbol*);
public:
	BmpFormatter(string s, Composition& composition, int sir, int br) :Formater(s, composition), weight(sir), numPx(br) {};
	~BmpFormatter() { }
	virtual void form() override;
};
#endif