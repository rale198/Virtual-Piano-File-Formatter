#include "BMPFormatter.h"

void BmpFormatter::form()
{
	ofstream &file=*(new ofstream("elisa.bmp", ofstream::binary));
	filltheHashMap();

	generateMatrix();
	generateBMP(file);

	

	fillPx(file);
	file.close();
}

void BmpFormatter::generateBMP(ofstream& file)
{
	file << (char)0x42 << (char)0x4D;

	int map = weight * data.size();
	while (map % 8 != 0) map++;

	cout << map << endl;
	int wholemap = 54 + map;


	int prviBajt = wholemap << 24;
	prviBajt = prviBajt >> 24;
	int drugiBajt = wholemap << 16;
	drugiBajt = drugiBajt >> 24;
	int treciBajt = wholemap << 8;
	treciBajt = treciBajt >> 24;
	int cetvrtiBajt = wholemap >> 24;
	file << (char)prviBajt << (char)drugiBajt << (char)treciBajt << (char)cetvrtiBajt;

	file << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x36 << (char)0x00 << (char)0x00 << (char)0x00;
	file << (char)0x28 << (char)0x00 << (char)0x00 << (char)0x00;

	 prviBajt = weight << 24;
	prviBajt = prviBajt >> 24;
	 drugiBajt = weight << 16;
	drugiBajt = drugiBajt >> 24;
	 treciBajt = weight << 8;
	treciBajt = treciBajt >> 24;
	 cetvrtiBajt = weight >> 24;

	file << (char)prviBajt << (char)drugiBajt << (char)treciBajt << (char)cetvrtiBajt;

	 prviBajt = height << 24;
	prviBajt = prviBajt >> 24;
	 drugiBajt = height << 16;
	drugiBajt = drugiBajt >> 24;
	 treciBajt = height << 8;
	treciBajt = treciBajt >> 24;
	 cetvrtiBajt = height >> 24;

	 file << (char)prviBajt << (char)drugiBajt << (char)treciBajt << (char)cetvrtiBajt;


	file << (char)0x01 << (char)0x00 << (char)0x18 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00;

	 prviBajt = map << 24;
	prviBajt = prviBajt >> 24;
	 drugiBajt = map << 16;
	drugiBajt = drugiBajt >> 24;
	 treciBajt = map << 8;
	treciBajt = treciBajt >> 24;
	 cetvrtiBajt = map >> 24;

	file << (char)prviBajt << (char)drugiBajt << (char)treciBajt << (char)cetvrtiBajt;
	file << (char)0x13 << (char)0x0B << (char)0x00 << (char)0x00 << (char)0x13 << (char)0x0B << (char)0x00 << (char)0x00;

	file << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00;
}

void BmpFormatter::generateMatrix()
{
	int w=weight;
	string str = "";
	Part& left = composition.getLeft();
	left.iterToBegin();
	Measure* mleft = nullptr;
	for_each(composition.rbegin(), composition.rend(), [this, &w, &str,&mleft,&left](Measure* mes) {


		mleft = left.getIter();
		mleft->iterToBegin();

		for_each(mes->begin(), mes->end(), [this, &w, &str,&mleft](MusicSymbol*m)
		{
			MusicSymbol* ml = mleft->getNote();

			int wtmp = ml->getDuration().getDenominator() == 4 ? 2 : 1;

			if (w > wtmp)
			{
				w -= wtmp;
				calc_the_field(str,ml,m);
			}
			else
			{
				this->data.push_back(str);
				str = "";
				w = this->weight;
				calc_the_field(str,ml,m);
			}


			mleft->nextNote(1);

		});

		left.nextMeasure(1);
	
	
	});

}

void BmpFormatter::calc_the_field(string& str, MusicSymbol* ml, MusicSymbol* m)
{
	if (typeid(*ml) == typeid(Pause) && typeid(*m) == typeid(Pause))
	{
		str += to_string(255);
		str += ' ';
		str += to_string(255);;
		str += ' ';
		str += to_string(255);;
		str += ' ';
	}
	else if (typeid(*ml) == typeid(Note))
	{
		
		fillNote(str,ml);
	}
	else if (typeid(*m) == typeid(Note))
	{
		fillNote(str, m);
	}
	else if (typeid(*m) == typeid(Chord) && typeid(*ml) == typeid(Chord))
	{
		fillChords(str, m, ml);
	}
}
void BmpFormatter::fillPx(ofstream& file)
{
	for_each(data.rbegin(), data.rend(), [this,&file](string s)
	{
		std::string delimiter = " ";

		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			int br = std::stoi(token);
			unsigned prviBajt = br << 24;
			prviBajt = prviBajt >> 24;
			cout << prviBajt << endl;
			file << (char)prviBajt;

			s.erase(0, pos + delimiter.length());
		}
	});
}

int*BmpFormatter::fillNote(string& str, MusicSymbol*ml)
{

	Note* left = (Note*)ml;
	int oct = left->getOctave();

	string nt = left->getHeight();
	if (left->isSharp()) nt += "#";

	int * a = mapa[nt];
	int valG, valB, valR;

	if (a[RED] < 0) cout << nt << endl;
	if (oct == 2)
	{
		valB = x2(a[BLUE]);
		valG = x2(a[GREEN]);
		valR = x2(a[RED]);
	}
	else if (oct == 3)
	{
		valB = x3(a[BLUE]);
		valG = x3(a[GREEN]);
		valR = x3(a[RED]);
	}
	else if (oct == 4)
	{
		valB = x4(a[BLUE]);
		valG = x4(a[GREEN]);
		valR = x4(a[RED]);
	}
	else if (oct == 5)
	{
		valB = x5(a[BLUE]);
		valG = x5(a[GREEN]);
		valR = x5(a[RED]);
	}
	else
	{
		valB = x6(a[BLUE]);
		valG = x6(a[GREEN]);
		valR = x6(a[RED]);
	}
	str += to_string(valB);
	str += " ";
	str += to_string(valG);
	str += " ";
	str += to_string(valR);
	str += " ";

	int *ab = new int[3]{ valR,valG,valB };

	return ab;
}

void BmpFormatter::setPause(string& str)
{
	str += to_string(255);
	str += ' ';
	str += to_string(255);;
	str += ' ';
	str += to_string(255);;
	str += ' ';
}

void BmpFormatter::fillChords(string&str, MusicSymbol* ml, MusicSymbol* mr)
{

	int valR, valG, valB;
	valR = valG = valB = 0;

	if (ml->getDuration().getNumerator()==0&&mr->getDuration().getNumerator()==0)
	{
		Chord* cl = (Chord*)ml;
		Chord* cr = (Chord*)mr;

		for_each(cl->begin(), cl->end(), [this, &str,&valB,&valG,&valR](Note* note)
		{
			int*a = this->fillNote(str,note);

			valB += a[BLUE];
			valG += a[GREEN];
			valR += a[RED];

		});

		for_each(cr->begin(), cr->end(), [this, &str, &valB, &valG, &valR](Note* note)
		{
			int*a = this->fillNote(str, note);

			valB += a[BLUE];
			valG += a[GREEN];
			valR += a[RED];

		});

		valB = valB / (cl->size() * 2);
		valR = valR / (cl->size() * 2);
		valG = valG / (cl->size() * 2);
	}
	else if (ml->getDuration().getNumerator() == 0)
	{
		Chord* cr = (Chord*)ml;
		for_each(cr->begin(), cr->end(), [this, &str, &valB, &valG, &valR](Note* note)
		{
			int*a = this->fillNote(str, note);

			valB += a[BLUE];
			valG += a[GREEN];
			valR += a[RED];

		});

		valB = valB / cr->size() ;
		valR = valR / (cr->size());
		valG = valG / (cr->size());
	}
	else if(mr->getDuration().getNumerator()==0)
	{
		Chord* cr = (Chord*)mr;
		for_each(cr->begin(), cr->end(), [this, &str, &valB, &valG, &valR](Note* note)
		{
			int*a = this->fillNote(str, note);

			valB += a[BLUE];
			valG += a[GREEN];
			valR += a[RED];

		});

		valB = valB / cr->size();
		valR = valR / (cr->size());
		valG = valG / (cr->size());
	}

	str += to_string(valB);
	str += " ";
	str += to_string(valG);
	str += " ";
	str += to_string(valR);
	str += " ";
}
void BmpFormatter::filltheHashMap()
{
		int* c = new int[3];
		c[RED] = 255;
		c[GREEN] = c[BLUE] = 0;

		mapa["C"] = c;

		int* cs = new int[3];
		cs[RED] = 255;
		cs[GREEN] = 127;
		cs[BLUE] = 0;

		mapa["C#"] = cs;

		int*d = new int[3];

		d[RED] = d[GREEN] = 255;
		d[BLUE] = 0;

		mapa["D"] = d;

		int* ds = new int[3];
		ds[RED] = 127;
		ds[GREEN] = 255;
		ds[BLUE] = 0;

		mapa["D#"] = ds;

		int*e = new int[3];

		e[RED] = e[BLUE] = 0;
		e[GREEN] = 255;

		mapa["E"] = e;

		int*b = new int[3];
		b[RED] = 255;
		b[GREEN] = 0;
		b[BLUE] = 127;

		mapa["B"] = b;

		int *f = new int[3];

		f[RED] = 0;
		f[GREEN] = 255;
		f[BLUE] = 127;

		mapa["F"] = f;

		int*fs = new int[3];

		fs[RED] = 0;
		fs[GREEN] = fs[BLUE] = 255;

		mapa["F#"] = fs;

		int*g = new int[3];
		g[RED] = 0;
		g[GREEN] = 127;
		g[BLUE] = 255;

		mapa["G"] = g;

		int*gs = new int[3];

		gs[RED] = gs[GREEN] = 0;
		gs[BLUE] = 255;

		mapa["G#"] = gs;

		int *a = new int[3];

		a[RED] = 127;
		a[GREEN] = 0;
		a[BLUE] = 255;

		mapa["A"] = a;

		int*as = new int[3];

		as[RED] = as[BLUE] = 255;
		as[GREEN] = 0;

		mapa["A#"] = as;
}