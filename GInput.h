#ifndef _GINPUT_H_
#define _GINPUT_H_

class GInput {
public:

	friend ostream& operator<<(ostream& os, const GInput& g)
	{
		os << "*** NE MOZETE RADITI NISTA DOK NE UCITATE KOMPOZICIJU ***" << endl;
		return os;
	}
};
#endif 