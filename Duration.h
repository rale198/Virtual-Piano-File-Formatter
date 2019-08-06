#ifndef _DURATION_H_
#define _DURATION_H_

#include "GDenominator.h"
class Duration
{

private:

	int im; //denominator
	int br; //numerator

public:

	Duration(int i, int b) :im(i), br(b)
	{

		if (im != 4 && im != 8) throw GDenominator();
	}

	int getNumerator() const { return br; }
	int getDenominator() const { return im; }


	friend Duration operator-(const Duration& a, const Duration& b)
	{
		if(a.getDenominator()== b.getDenominator()) 
		return Duration(b.getDenominator(), a.getNumerator()- b.getNumerator());
		
		if(a.getDenominator()<b.getDenominator())
			return Duration(b.getDenominator(), 2*a.getNumerator() - b.getNumerator());
		return Duration(a.getDenominator(),  a.getNumerator() - 2*b.getNumerator());
	}

	friend bool operator>=(const Duration& a, const Duration& b)
	{
		Duration d = (a - b);
		return d.getNumerator() >= 0;
	}


	friend ostream& operator<<(ostream& os, const Duration& d)
	{
		os << "(" << d.getNumerator() << "/" << d.getDenominator() << ")";
		return os;
	}
};

#endif