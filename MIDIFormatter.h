#ifndef _MIDIFOR_H_
#define _MIDIFOR_H_

#include "Formater.h"

#include "MidiFile.h"
#include "MidiEvent.h"
#include "MidiEventList.h"
#include "MidiMessage.h"
#include "Binasc.h"
#include "Options.h"

class MidiFormatter :public Formater
{
public:
	MidiFormatter(string s, Composition& composition) :Formater(s, composition) {};
	virtual void form() override;
};
#endif