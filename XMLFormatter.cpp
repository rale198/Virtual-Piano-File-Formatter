#include "XMLFormatter.h"

void XmlFormatter::form() {

   ofstream& outfile=*(new ofstream(this->s+".txt"));

   this->addBeggining(outfile);
   this->addRightHand(outfile);
   this->addLeftHand(outfile);

    outfile << "</score-partwise>";
	outfile.close();
	
}

void XmlFormatter::addBeggining(ostream& output)
{

	output << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << endl;
	output << "<!DOCTYPE score-partwise PUBLIC" << endl;
	output << "\"-//Recordare//DTD MusicXML 3.1 Partwise//EN\"" << endl;
	output << "\"http://www.musicxml.org/dtds/partwise.dtd \">" << endl;
	output << "	<score-partwise version=\"3.1\">" << endl;
	output << "	<part-list>" << endl;
	output << "	<score-part id =\"Right\"></score-part>" << endl;
	output << "	<score-part id =\"Left\"></score-part>" << endl;
	output << "	</part-list>" << endl;
}


void XmlFormatter::addRightHand(ostream& output)
{

	Part& rightHand=this->composition.getRight();

	output << "<part id=\"Right\">" << endl;
	output << "<measure>" << endl;
	output << "<attributes>" << endl;
	output << "<divisions>2</divisions>" << endl;
	output << "<time>" << endl;
	output << "<beats>" << composition.getDur().getNumerator()<<"</beats>"<<endl;
	output << "<beat-type>" << composition.getDur().getDenominator() << "</beat-type>" << endl;
	output << "</time>" << endl;
	output << "<clef>" << endl;
	output << "<sign>G</sign>" << endl;
	output << "<line>2</line>" << endl;
	output << "</clef>" << endl;
	output << "</attributes>" << endl << endl;

	const string flagNote[] = { "\"start\"","\"end\"" };
	const string flagChord[] = { "\"start\"","\"end\"" };
	int i = 0;
	int j = 0;
	bool firstMeasure = true;
	for_each(rightHand.begin(), rightHand.end(), [this,&firstMeasure,&output,&flagNote,&flagChord,&j,&i](Measure* m) {

		if (firstMeasure)
		{
			firstMeasure = false;
		}
		else output << "<measure>" << endl;

		for_each(m->begin(), m->end(), [this, &output, &flagNote, &i, &flagChord, &j ](MusicSymbol* mus) {


			if (typeid(*mus) == typeid(Pause))
			{
				output << "<note>" << endl;
				output << "<rest/>" << endl;
				int dur = (mus->getDuration().getDenominator() == 8) ? 1 : 2;
				output << "<duration>" << dur << "</duration>" << endl;
				output << "</note>" << endl;
			}
			else if (typeid(*mus) == typeid(Note))
			{
				int dur = (mus->getDuration().getDenominator() == 8) ? 1 : 2;

				output << "<note>" << endl;
				output << "<pitch>" << endl;
				output << "<step>" << ((Note*)mus)->getHeight() << "</step>" << endl;
				output << "<octave>" << ((Note*)mus)->getOctave() << "</octave>" << endl;
				if (((Note*)mus)->isSharp()) output << "<alter>1</alter>" << endl;
				output << "</pitch>" << endl;
				output << "<duration>" << dur << "</duration>" << endl;

				if (mus->isDecomposed())
				{
					output << "<tie type=" << flagNote[i] << "/>" << endl;
					i = (i + 1) % 2;
				}

				output << "</note>" << endl;
			}
			else if((typeid(*mus))==typeid(Chord))
			{
				
				Chord* chord = (Chord*)mus;

				if (chord->getPause().getDuration().getDenominator() == 8 && chord->getPause().getDuration().getNumerator() > 0)
				{
					output << "<note>" << endl;
					output << "<rest/>" << endl;
					output << "<duration>1</duration>" << endl;
					output << "</note>" << endl;
				}
				else if (chord->getPause().getDuration().getDenominator() == 4 && chord->getPause().getDuration().getNumerator() > 0)
				{
					output << "<note>" << endl;
					output << "<rest/>" << endl;
					output << "<duration>2</duration>" << endl;
					output << "</note>" << endl;
				}
				else
				{

					bool flagFirst = true;
					bool decomposed = mus->isDecomposed();
					for_each(((Chord*)mus)->begin(), ((Chord*)mus)->end(), [this, &decomposed, &flagFirst, &output, &flagChord, &j](Note* note) {

						if (flagFirst == true)
						{
							flagFirst = false;

							int dur = (note->getDuration().getDenominator() == 8) ? 1 : 2;

							output << "<note>" << endl;
							output << "<pitch>" << endl;
							output << "<step>" << note->getHeight() << "</step>" << endl;
							output << "<octave>" << note->getOctave() << "</octave>" << endl;
							if (note->isSharp()) output << "<alter>1</alter>" << endl;
							output << "</pitch>" << endl;
							output << "<duration>" << dur << "</duration>" << endl;

							if (decomposed)
							{
								output << "<tie type=" << flagChord[j] << "/>" << endl;
							}
							output << "</note>" << endl;
						}
						else
						{
							int dur = (note->getDuration().getDenominator() == 8) ? 1 : 2;

							output << "<note>" << endl;
							output << "<chord/>" << endl;
							output << "<pitch>" << endl;
							output << "<step>" << note->getHeight() << "</step>" << endl;
							output << "<octave>" << note->getOctave() << "</octave>" << endl;
							if (note->isSharp()) output << "<alter>1</alter>" << endl;
							output << "</pitch>" << endl;
							output << "<duration>" << dur << "</duration>" << endl;

							if (decomposed)
							{
								output << "<tie type=" << flagChord[j] << "/>" << endl;
							}

							output << "</note>" << endl;
						}
					});

					j = (j + 1) % 2;
				}

			}


		});

		output << "</measure>" << endl;
	});

	output << "</part>" << endl<<endl;
		
	
}

void XmlFormatter::addLeftHand(ostream& output)
{

	Part& leftHand = this->composition.getLeft();

	output << "<part id=\"Left\">" << endl;
	output << "<measure>" << endl;
	output << "<attributes>" << endl;
	output << "<divisions>2</divisions>" << endl;
	output << "<time>" << endl;
	output << "<beats>" << composition.getDur().getNumerator() << "</beats>" << endl;
	output << "<beat-type>" << composition.getDur().getDenominator() << "</beat-type>" << endl;
	output << "</time>" << endl;
	output << "<clef>" << endl;
	output << "<sign>F</sign>" << endl;
	output << "<line>4</line>" << endl;
	output << "</clef>" << endl;
	output << "</attributes>" << endl << endl;

	const string flagNote[] = { "\"start\"","\"end\"" };
	bool firstMeasure = true;
	int i = 0;
	const string flagChord[]= { "\"start\"","\"end\"" };
	int j = 0;
	for_each(leftHand.begin(), leftHand.end(), [this,&firstMeasure, &output, &flagNote,&flagChord,&j, &i](Measure* m) {

		if (firstMeasure)
		{
			firstMeasure = false;
		}
		else output << "<measure>" << endl;
		for_each(m->begin(), m->end(), [this, &output, &flagNote,&flagChord,&j, &i](MusicSymbol* mus) {


			if (typeid(*mus) == typeid(Pause))
			{
				output << "<note>" << endl;
				output << "<rest/>" << endl;
				int dur = (mus->getDuration().getDenominator() == 8) ? 1 : 2;
				output << "<duration>" << dur << "</duration>" << endl;
				output << "</note>" << endl;
			}
			else if (typeid(*mus) == typeid(Note))
			{
				int dur = (mus->getDuration().getDenominator() == 8) ? 1 : 2;

				output << "<note>" << endl;
				output << "<pitch>" << endl;
				output << "<step>" << ((Note*)mus)->getHeight() << "</step>" << endl;
				output << "<octave>" << ((Note*)mus)->getOctave() << "</octave>" << endl;
				if (((Note*)mus)->isSharp()) output << "<alter>1</alter>" << endl;
				output << "</pitch>" << endl;
				output << "<duration>" << dur << "</duration>" << endl;

				if (mus->isDecomposed())
				{
					output << "<tie type=" << flagNote[i] << "/>" << endl;
					i = (i + 1) % 2;
				}

				output << "</note>" << endl;
			}
			else if(typeid(*mus)==typeid(Chord))
			{
				Chord* chord = (Chord*)mus;

				if (chord->getPause().getDuration().getDenominator() == 8&& chord->getPause().getDuration().getNumerator() > 0)
				{
					output << "<note>" << endl;
					output << "<rest/>" << endl;
					output << "<duration>1</duration>" << endl;
					output << "</note>" << endl;
				}
				else if (chord->getPause().getDuration().getDenominator() == 4 && chord->getPause().getDuration().getNumerator() > 0)
				{
					output << "<note>" << endl;
					output << "<rest/>" << endl;
					output << "<duration>2</duration>" << endl;
					output << "</note>" << endl;
				}
				else 
				{

					bool flagFirst = true;
					bool decomposed = mus->isDecomposed();
					for_each(((Chord*)mus)->begin(), ((Chord*)mus)->end(), [this,&decomposed, &flagFirst, &output, &flagChord, &j](Note* note) {

						if (flagFirst == true)
						{
							flagFirst = false;

							int dur = (note->getDuration().getDenominator() == 8) ? 1 : 2;

							output << "<note>" << endl;
							output << "<pitch>" << endl;
							output << "<step>" << note->getHeight() << "</step>" << endl;
							output << "<octave>" << note->getOctave() << "</octave>" << endl;
							if (note->isSharp()) output << "<alter>1</alter>" << endl;
							output << "</pitch>" << endl;
							output << "<duration>" << dur << "</duration>" << endl;

							if (decomposed)
							{
								output << "<tie type=" << flagChord[j] << "/>" << endl;
							}
							output << "</note>" << endl;
						}
						else
						{
							int dur = (note->getDuration().getDenominator() == 8) ? 1 : 2;

							output << "<note>" << endl;
							output << "<chord/>" << endl;
							output << "<pitch>" << endl;
							output << "<step>" << note->getHeight() << "</step>" << endl;
							output << "<octave>" << note->getOctave() << "</octave>" << endl;
							if (note->isSharp()) output << "<alter>1</alter>" << endl;
							output << "</pitch>" << endl;
							output << "<duration>" << dur << "</duration>" << endl;

							if (decomposed)
							{
								output << "<tie type=" << flagChord[j] << "/>" << endl;
							}

							output << "</note>" << endl;
						}
					});

					j = (j + 1) % 2;
				}
			}


		});

		output << "</measure>" << endl;
	});

	output << "</part>" << endl;

}