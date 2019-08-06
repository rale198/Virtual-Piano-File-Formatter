#include "HashTable.h"

void Composition::load(string str, HashTable& h)
{

	ifstream file(str);
	string s;

	regex rx("(\\[[^\\[\\]]*\\])|([^\\[\\]]*)");

	Measure* rightClk = new Measure(this->getDur());
	Measure* leftClk = new Measure(this->getDur());

	while (getline(file, s))
	{

		sregex_iterator begin(s.begin(), s.end(), rx);
		sregex_iterator end;

		int i = 1;

		while (begin != end)
		{
			smatch res = *begin;
			
			if (res.str(2) == ""&&res.str(1)!="")
			{
				string s = res.str(1);

				if (string(1, s[2]) == " ")
				{
					for(int i=1;i<(int)s.size()-1;i++)
						if (string(1, s[i]) != " ")
						{
							string str = h[(string(1, s[i]))].first; // for example C#4
							int m = h[(string(1, s[i]))].second; //midiValue

							pt p = addSimpleNote(rightClk, leftClk, str, m,Duration(8,1));
							rightClk = p.first;
							leftClk = p.second;
						}
				}
				else
				{
				
					pt p = addChord(rightClk, leftClk, res.str(1),h);
					rightClk = p.first;
					leftClk = p.second;
				}
			}
			else if (res.str(1) == ""&&res.str(2)!="")
			{
				string s = res.str(2);
				for (int i = 0; i < (int)s.size(); i++)
				{

					if (string(1, s[i]) == " ")
					{
						pt pt = addSmallPause(rightClk, leftClk);
						rightClk = pt.first;
						leftClk = pt.second;
					}
					else if (string(1, s[i]) == "|")
					{
						pt pt= addBigPause(rightClk, leftClk);
						rightClk = pt.first;
						leftClk = pt.second;
					}
					else if (string(1, s[i]) != "\n")
					{
						string str = h[(string(1, s[i]))].first; // for example C#4
						int m = h[(string(1, s[i]))].second; //midiValue

						pt p = addSimpleNote(rightClk, leftClk, str, m, Duration(4,1));
						rightClk = p.first;
						leftClk = p.second;
					}
				}
			}
			begin++;
		}
	}
	fillLastMeasure(rightClk, leftClk);
}
void Composition::fillLastMeasure(Measure*rightClk, Measure*leftClk)
{
	while (rightClk->getDur().getNumerator() > 0)
	{
		addPause(rightClk, Duration(8, 1));
		addPause(leftClk, Duration(8, 1));

		if (Duration(8, 0) >= rightClk->getDur())
		{
			addMeasure(&rightClk, &leftClk);
			break;
		}
	}
}
pt Composition::addBigPause(Measure* rightClk,Measure* leftClk)
{
	if (rightClk->getDur() >= Duration(4, 1))
	{

		addPause(rightClk, Duration(4, 1));
		addPause(leftClk, Duration(4, 1));

		 if (Duration(4, 0) >= leftClk->getDur())
		 {
			 addMeasure(&rightClk, &leftClk);
		 }

		 pt pt = pair<Measure*, Measure*>(rightClk, leftClk);
		 return pt;
	}
	else
	{
		pair<Measure*, Measure*>tmp;
		tmp=addSmallPause(rightClk, leftClk);
		rightClk = tmp.first;
		leftClk = tmp.second;
		tmp=addSmallPause(rightClk, leftClk);
		rightClk = tmp.first;
		leftClk = tmp.second;
	}
	pt pt = pair<Measure*, Measure*>(rightClk, leftClk);
	return pt;
}

pt Composition::addSmallPause(Measure* rightClk,Measure*leftClk)
{
	addPause(rightClk,Duration(8,1));
	addPause(leftClk,Duration(8, 1));

	if (Duration(8, 0) >= rightClk->getDur())
	{
		addMeasure(&rightClk, &leftClk);
	}

	 pt pt = pair<Measure*, Measure*>(rightClk, leftClk);
	 return pt;
}

void Composition::addMeasure(Measure**rightClk, Measure**leftClk)
{
	this->addRight(*rightClk);
	this->addLeft(*leftClk);

	*rightClk = new Measure(this->getDur());
	*leftClk = new Measure(this->getDur());
}

void Composition::addPause(Measure* clk,Duration d)
{
	clk->add(new Pause(d,false));
	clk->setDur(clk->getDur() - d);
}

pt Composition::addSimpleNote(Measure* rightClk, Measure* leftClk, string str, int m,Duration d)
{
	if (str.size() == 2) //obrada nepovisenih nota
	{
		int oct = str[1] - 48;
		if (oct > 3) //nepovisena nota, desna ruka
		{

			if (rightClk->getDur() >= d)
			{
				Note *nota = new Note(d, false, "", string(1, str[0]), oct, m);

				rightClk->setDur(rightClk->getDur() - d);

				rightClk->add(nota);

				addPause(leftClk, d);

				if (Duration(8, 0) >= rightClk->getDur()) addMeasure(&rightClk, &leftClk);

			}
			else
			{
				rightClk->setDur(Duration(8, 0));
				rightClk->add(new Note(Duration(8,1), true, "", string(1, str[0]), oct, m));
				addPause(leftClk, Duration(8,1));

				addMeasure(&rightClk, &leftClk);

				addPause(leftClk, Duration(8,1));
				rightClk->setDur(rightClk->getDur() - Duration(8,1));
				rightClk->add(new Note(Duration(8,1), true, "", string(1, str[0]), oct, m));

			}

		} //leva ruka
		else if (leftClk->getDur() >= d)
		{
			Note *nota = new Note(d, false, "#", string(1, str[0]), oct, m);

			leftClk->setDur(leftClk->getDur() - d);

			leftClk->add(nota);

			addPause(rightClk, d);

			if (Duration(8, 0) >= leftClk->getDur()) addMeasure(&rightClk, &leftClk);
		}
		else
		{
			Duration d = Duration(8, 1);

			leftClk->add(new Note(d, true, "#", string(1, str[0]), oct, m));
			addPause(rightClk, d);

			addMeasure(&rightClk, &leftClk);

			addPause(rightClk, d);
			leftClk->setDur(leftClk->getDur() - d);
			leftClk->add(new Note(d, true, "#", string(1, str[0]), oct, m));
		}
	}
	else if (str.size() == 3) //obrada povisenih nota
	{
		int oct = str[2] - 48;
		if (oct > 3)
		{

			if (rightClk->getDur() >= d)
			{
				Note *nota = new Note(d, false, "#", string(1, str[0]), oct, m);

				rightClk->setDur(rightClk->getDur() - d);

				rightClk->add(nota);

				addPause(leftClk, d);

				if (Duration(8, 0) >= rightClk->getDur()) addMeasure(&rightClk, &leftClk);
			}
			else
			{

				Duration d = Duration(8, 1);

				rightClk->setDur(Duration(8, 0));
				rightClk->add(new Note(d, true, "#", string(1, str[0]), oct, m));
				addPause(leftClk, d);

				addMeasure(&rightClk, &leftClk);

				addPause(leftClk, d);
				rightClk->setDur(rightClk->getDur() - d);
				rightClk->add(new Note(d, true, "#", string(1, str[0]), oct, m));
			}
		}
		else
		{
			if (leftClk->getDur() >= d)
			{
				Note *nota = new Note(d, false, "#", string(1, str[0]), oct, m);

				leftClk->setDur(leftClk->getDur() - d);

				leftClk->add(nota);

				addPause(rightClk,d);

				if (Duration(8, 0) >= leftClk->getDur()) addMeasure(&rightClk, &leftClk);
			}
			else
			{
				Duration d = Duration(8, 1);

				leftClk->add(new Note(d, true, "#", string(1, str[0]), oct, m));
				addPause(rightClk,d);

				addMeasure(&rightClk, &leftClk);

				addPause(rightClk, d);
				leftClk->setDur(leftClk->getDur() - d);
				leftClk->add(new Note(d, true, "#", string(1, str[0]), oct, m));
			}
		}
	}

	pt p = pt(rightClk, leftClk);
	return p;
}

pt Composition::addChordNote(Measure* rightClk, Measure* leftClk, Note* leftChord, Note* rightChord)
{
	Duration d = Duration(4, 1);

	Duration dh = Duration(8, 1);
	if (rightClk->getDur() >= d)
	{
		rightClk->add(rightChord);
		leftClk->add(leftChord);

		rightClk->setDur(rightClk->getDur() - d);
		leftClk->setDur(rightClk->getDur());

		if (Duration(4, 0) >= rightClk->getDur())
		{
			addMeasure(&rightClk, &leftClk);
		}
	}
	else
	{
		chordDec(rightChord);
		chordDec(leftChord);

		rightClk->add(rightChord);
		leftClk->add(leftChord);

		addMeasure(&rightClk, &leftClk);

		chordDec(rightChord);
		chordDec(leftChord);

		rightClk->add(rightChord);
		leftClk->add(leftChord);
	}
	pt p = pt(rightClk, leftClk);
	return p;
}
void Composition::chordDec(Note* clk)
{
	clk->setDur(Duration(8, 1));
	clk->setDecomposed();
	((Chord*)clk)->setPause(Duration(8, 1));
}
pt Composition::addChord(Measure* rightClk,Measure* leftClk,string notes, HashTable& h)
{
	Chord *chLeft = new Chord();
	Chord *chRight = new Chord();

	for (int i = 1; i < (int)notes.size() - 1; i++)
	{
		string str = h[(string(1, notes[i]))].first; // for example C#4
		int m = h[(string(1, notes[i]))].second;

		Note * nota = nullptr;
		int oct = 0;
		if (str.size() == 2)
		{
			oct = str[1] - 48;

			nota = new Note(Duration(4, 1), false, "", string(1, str[0]), oct, m);

		}
		else
		{
			oct = str[2] - 48;

			nota = new Note(Duration(4, 1), false, "#", string(1, str[0]), oct, m);
		}
		if (oct > 3) chLeft->add(nota);
		else chRight->add(nota);
	}
	if (chLeft->size() == 0) chLeft->setPause();
	if (chRight->size() == 0) chRight->setPause();
	pt p = addChordNote(rightClk, leftClk, chRight,chLeft);
	return p;
}


pt Composition::nextMeasure()
{
	pt p;
	p.first= rightHand->nextMeasure();
	p.second= leftHand->nextMeasure();

	return p;
}

pt Composition::prevMeasure()
{
	pt p;
	p.first = rightHand->prevMeasure();
	p.second = leftHand->prevMeasure();

	return p;
}

ptNote Composition::nextNote()
{
	ptNote p;
	p.first= rightHand->nextNote();
	p.second= leftHand->nextNote();

	return p;
}
ptNote Composition::prevNote()
{
	ptNote p;
	p.first = rightHand->prevNote();
	p.second = leftHand->prevNote();

	return p;
}

void Composition::changeOctave(int oct)
{
	//if (oct > 6 || oct < 2) throw GOctave();

	rightHand->changeOctave(oct);
	leftHand->changeOctave(oct);
}

void Composition::changeH(string h)
{
	rightHand->changeH(h);
	leftHand->changeH(h);
}

void Composition::changeSharp(string s)
{
	rightHand->changeSharp(s);
	leftHand->changeSharp(s);
}

Composition& Composition::newOctave(const int& oct)
{
	if (oct>4||oct<-4) throw GOctave();

	for_each(rightHand->begin(), rightHand->end(), [&oct](Measure*p) {p->changeOctave(oct); });
	for_each(leftHand->begin(), leftHand->end(), [&oct](Measure*p) {p->changeOctave(oct); });

	return*this;
}

void Composition::write(ostream& os) 
{
	string strRight = "";
	string strLeft = "";
	int i = 70;


	Measure* mright = nullptr;
	Measure* mleft = nullptr;
	leftHand->iterToBegin();

	for_each(rightHand->begin(),rightHand->end(),[this,&mleft,&strRight,&strLeft,&i](Measure* mright){
	

		mleft = leftHand->getIter();
		string sr= mright->toString();
		string sl= mleft->toString();

		if (sr.size() > sl.size())
		{
			for (int i = 0; i <(int) (sr.size() - sl.size()); i++)
				sl += " ";
		}
		else if (sr.size() < sl.size())
		{
			for (int i = 0; i <(int) (sl.size() - sr.size()); i++)
				sr += " ";
		}

		strRight += sr;
		strLeft += sl;

		if (i <= (int)strRight.size())
		{
			strRight += "|";
			strLeft += "|";

			cout << strRight << endl;
			cout << strLeft << endl << endl;

			i = 70;
			strRight = "";
			strLeft = "";
		}

		else i -= strRight.size();

		leftHand->nextMeasure(1);
	}
	);
}