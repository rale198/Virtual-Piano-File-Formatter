#include "HashTable.h"

void HashTable::parse(string name)
{
	ifstream file(name);

	string s;
	regex rx("(.),(.*),(.*[^\\n])");
	int i = 0;
	while (getline(file, s))
	{
		smatch result;
		if (regex_match(s, result, rx))
		{
			pair<string, unsigned int> opis = pair<string, unsigned int>(result.str(2), atoi(result.str(3).c_str()));
			this->addSymbol(result.str(1), opis);
		}

	}
}

void HashTable::write(ostream& os) const
{
	using pts = pair<string, pair<string, int>>;
	for_each((*this).begin(), (*this).end(), [&os](pts opis) {os << "Code: " << opis.first << " Note && MidiInfo " << opis.second.first << " " << opis.second.second << endl;; });
}

