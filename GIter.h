#ifndef _GITER_H_
#define _GITER_H_
class GIter {
public:
	friend ostream& operator<<(ostream& os, const GIter& g)
	{
		os << "*** WRONG ITERATING!!! ***" << endl;
		return os;
	}
};
#endif // !_GITER_H_
