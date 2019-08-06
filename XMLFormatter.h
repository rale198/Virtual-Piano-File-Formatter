#ifndef _XMLF_H_
#define _XMLF_H_
#include "Formater.h"
class XmlFormatter :public Formater
{

private:

	void addBeggining(ostream&);
	void addRightHand(ostream&);
	void addLeftHand(ostream&);
	const string begging[10];

public:

	XmlFormatter(string s, Composition& composition) :Formater(s, composition) {};
	virtual void form() override;
};
#endif