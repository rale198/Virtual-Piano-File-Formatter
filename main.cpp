#include "HashTable.h"
#include "GInput.h"
#include "MIDIFormatter.h"
#include "XMLFormatter.h"
#include "BMPFormatter.h"
int main(int argc, const char * argv[])
{
	Main *main = new Main();
	HashTable *h = new HashTable();

	h->parse(argv[1]);

	Composition* composition = nullptr;
	int idx = 0;
	bool finish = false;
	bool pass = false;
	//cout << *h << endl;
	string s; //ovde pamtim koji je trenutno fajl ucitan
	string str = "C:\\Users\\sr170398d\\Desktop\\Rastko\\2.godina\\POOP\\Projekti\\Projekat1Sve\\input\\";

	while (finish == false)
	{

		try {
			main->menu();
			cout << "Enter one of the following options in the menu above" << endl;

			cin >> idx;

			switch (idx) {
			case 0: finish = true; break;
			case 1: {
				pass = true;
				cout << "Unesite putanju i naziv za ulazni fajl, a zatim i duzinu takta u kompoziciji" << endl;

				int im, br;

				cin >> s >> im >> br;
				composition = new Composition(new Part(), new Part(), Duration(im, br));
				composition->load(str + s + ".txt" , *h);
				break;
			}
			case 2:
				if (!pass) throw GInput();
				cout << *composition << endl;
				break;

			case 3:
			{

				composition->getRight().iterToBegin();
				composition->getLeft().iterToBegin();
				if (!pass) throw GInput();
				int idx = 0;
				bool finish = false;
				while (!finish)
				{
					main->iteriranjeTakt();
					cout << "Enter one of the following options in the menu above" << endl;

					cin >> idx;
					switch (idx)
					{
					case 1: {

						pt m=composition->nextMeasure();
						cout << *(m.first) << endl<<*(m.second)<<endl;

						break;
					}
					case 2:
					{
						pt m = composition->prevMeasure();
						cout << *(m.first) << endl << *(m.second) << endl;

						break;
					}
					case 3:
					{

						int idx;
						bool finish = false;
						while (!finish) {
							main->iteriranjeNote();
							cout << "Enter one of the following options in the menu above" << endl;

							cin >> idx;
							switch (idx)
							{
							case 1: {
								ptNote p = composition->nextNote();
								cout << *(p.first) << endl << *(p.second) << endl;
								break;
							}
							case 2: 
							{
								ptNote p = composition->prevNote();
								cout << *(p.first) << endl << *(p.second) << endl;
								break;
							}
							case 3:
							{
								cout << "Unesite vrednost oktave";
								int oct;
								cin >> oct;

								composition->changeOctave(oct);
								break;
							}
							case 4:
							{
								cout << "Unesite visinu";
								string str;
								cin >> str;
								composition->changeH(str);
								break;
							}
							case 5:
							{
								composition->changeSharp("#");

								break;
							}
							case 6:
							{
								composition->changeSharp("");

								break;
							}
							default: finish = true; break;
							}
						}
						break;
					}
					default: finish = true; break;
					}
				}
				break;
			}
			case 4: {
				int im, br;

				cin >> im >> br;
				composition = new Composition(new Part(), new Part(), Duration(im, br));
				composition->load(str + s, *h);
				break;
			}
			case 5:
			{
				int oct;
				cin >> oct;

				composition->newOctave(oct);
				break;
			}
			case 6: {
				string s;
				cout << "Unesite ime fajla" << endl;
				cin >> s;
				Formater * f = new MidiFormatter(s,*composition);
				f->form();
				break;
			}
			case 7:
			{
				string s;
				cin >> s;
				Formater * f = new XmlFormatter(s, *composition);
				f->form();
				break;
			}
			case 8:
			{
				
				cout << "Unesite sirinu slike i broj piksela" << endl;
				int sirina, br;
				cin >> sirina >> br;
				Formater * f = new BmpFormatter(s, *composition,sirina,br);
				f->form();
				break;
			}
			default: break;
			}

		}
		catch (GDenominator g) { cout << g << endl; }
		catch (GOctave g) { cout << g << endl; }
		catch (GInput g) { cout << g << endl; }
		catch (GIter g) { cout << g << endl; }

	}

	cout << "End of program!" << endl;
	system("pause");
	delete main;
	delete h;
	return 0;
}