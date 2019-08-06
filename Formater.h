#ifndef _FORM_H_
#define _FORM_H_

#include "Composition.h"
class Formater {

protected:
	string s;
	Composition& composition;
public:
	Formater(string st,Composition& compos):s(st),composition(compos){}
	virtual void form() = 0;
	virtual ~Formater() {};
};

#endif