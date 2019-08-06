#include "MIDIFormatter.h"
using namespace smf;
void MidiFormatter::form()
{
	MidiFile outputfile;
	outputfile.absoluteTicks();
	vector<uchar> midievent;
	midievent.resize(3);
	int tpq = 48;
	outputfile.setTicksPerQuarterNote(tpq);
	outputfile.addTrack(1);

	int i = 0;
	int actiontime = 0;
	midievent[2] = 64;

	bool beenDec = false;
	bool beenDecChord = false;

	for_each(composition.rbegin(), composition.rend(), [&beenDecChord, &beenDec, &outputfile, &midievent, &actiontime, &tpq](Measure* m) {
		for_each(m->begin(), m->end(), [&beenDecChord, &beenDec, &outputfile, &midievent, &actiontime, &tpq](MusicSymbol* s) {

			midievent[0] = 0x90;

			int time = 0;

			if (typeid(*s) == typeid(Pause))
			{
				if (Duration(4, 1) >= ((Pause*)s)->getDuration())time = 2;
				else time = 1;

				actiontime += tpq / 2 * time;
			}
			else if (typeid(*s) == typeid(Note))
			{

				if (Duration(4, 1) >= ((Note*)s)->getDuration())
				{
					midievent[1] = ((Note*)s)->getMidi();
					time = 2;

					outputfile.addEvent(0, actiontime, midievent);
					actiontime += tpq / 2 * time;
					midievent[0] = 0x80;
					outputfile.addEvent(0, actiontime, midievent);
				}
				else
				{
					if (s->isDecomposed() == true && beenDec == false)
					{
						beenDec = true;
						time = 2;
						midievent[1] = ((Note*)s)->getMidi();

						outputfile.addEvent(0, actiontime, midievent);
						actiontime += tpq / 2 * time;
						midievent[0] = 0x80;
						outputfile.addEvent(0, actiontime, midievent);
					}
					else if (s->isDecomposed() && beenDec == true)
					{
						beenDec = false;
						time = 1;
					}
					else
					{
						midievent[1] = ((Note*)s)->getMidi();
						time = 1;

						outputfile.addEvent(0, actiontime, midievent);
						actiontime += tpq / 2 * time;
						midievent[0] = 0x80;
						outputfile.addEvent(0, actiontime, midievent);

					}
				}


			}
			else if (typeid(*s) == typeid(Chord))
			{
				Pause p = ((Chord*)s)->getPause();

				if (p.getDuration().getDenominator() == 8 && p.getDuration().getNumerator() > 0)
				{
					time = 1;
					actiontime += tpq / 2 * time;
				}
				else if (p.getDuration().getNumerator() == 4 && p.getDuration().getNumerator() > 0)
				{
					time = 2;
					actiontime += tpq / 2 * time;
				}

				else if ((s->isDecomposed() == true && beenDecChord == false) || (s->isDecomposed() == false))
				{
					time = 2;
					beenDecChord = true;
					for_each(((Chord*)s)->begin(), ((Chord*)s)->end(), [&midievent, &s, &time, &outputfile, &actiontime](Note* p)
					{
						midievent[1] = p->getMidi();

						outputfile.addEvent(0, actiontime, midievent);
						midievent[0] = 0x80;
						outputfile.addEvent(0, actiontime, midievent);
					}
					);
					actiontime += tpq / 2 * time;
				}
				else beenDecChord = false;
			}
		}
		);
	}
	);

	beenDec = false;
	beenDecChord = false;
	i = 0;
	actiontime = 0;

	for_each(composition.lbegin(), composition.lend(), [&beenDecChord, &beenDec, &outputfile, &midievent, &actiontime, &tpq](Measure* m)
	{
		for_each(m->begin(), m->end(), [&beenDecChord, &beenDec, &outputfile, &midievent, &actiontime, &tpq](MusicSymbol* s)
		{
			midievent[0] = 0x90;

			int time = 0;

			if (typeid(*s) == typeid(Pause))
			{
				if (Duration(4, 1) >= ((Pause*)s)->getDuration())time = 2;
				else time = 1;

				actiontime += tpq / 2 * time;
			}
			else if (typeid(*s) == typeid(Note))
			{
				if (Duration(4, 1) >= ((Note*)s)->getDuration())
				{
					midievent[1] = ((Note*)s)->getMidi();
					time = 2;

					outputfile.addEvent(1, actiontime, midievent);
					actiontime += tpq / 2 * time;
					midievent[0] = 0x80;
					outputfile.addEvent(1, actiontime, midievent);
				}
				else
				{
					if (s->isDecomposed() == true && beenDec == false)
					{
						beenDec = true;
						time = 2;
						midievent[1] = ((Note*)s)->getMidi();

						outputfile.addEvent(1, actiontime, midievent);
						actiontime += tpq / 2 * time;
						midievent[0] = 0x80;
						outputfile.addEvent(1, actiontime, midievent);
					}
					else if (s->isDecomposed() && beenDec == true)
					{
						beenDec = false;
						time = 1;
					}
					else
					{
						midievent[1] = ((Note*)s)->getMidi();
						time = 1;

						outputfile.addEvent(1, actiontime, midievent);
						actiontime += tpq / 2 * time;
						midievent[0] = 0x80;
						outputfile.addEvent(1, actiontime, midievent);

					}
				}
			}
			else if (typeid(*s) == typeid(Chord))
			{
				Pause p = ((Chord*)s)->getPause();

				if (p.getDuration().getDenominator() == 8 && p.getDuration().getNumerator() > 0)
				{
					time = 1;
					actiontime += tpq / 2 * time;
				}
				else if (p.getDuration().getNumerator() == 4 && p.getDuration().getNumerator() > 0)
				{
					time = 2;
					actiontime += tpq / 2 * time;
				}

				else if ((s->isDecomposed() == true && beenDecChord == false) || (s->isDecomposed() == false))
				{
					time = 2;
					beenDecChord = true;
					for_each(((Chord*)s)->begin(), ((Chord*)s)->end(), [&midievent, &s, &time, &outputfile, &actiontime](Note* p)
					{
						midievent[1] = p->getMidi();

						outputfile.addEvent(1, actiontime, midievent);
						midievent[0] = 0x80;
						outputfile.addEvent(1, actiontime, midievent);
					}
					);
					actiontime += tpq / 2 * time;
				}
				else beenDecChord = false;

			}
		}
		);
	}
	);

	outputfile.sortTracks();
	outputfile.write(this->s + ".mid");
}