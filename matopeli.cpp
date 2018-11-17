#include <iostream>
using namespace std;
int KysyValinta(void);

int main()
{
	int valinta;

	do // ajetaan loop lapi ainakin kerran
	{
		valinta = KysyValinta();
		switch (valinta) // valitsee casen valinnan saaman arvon mukaisesti
		{
		case 0:
			cout << "Peli suljetaan" << endl;
			return 0;
		case 1:
			break; // break poistuu switch-lauseesta seuraavaan
		case 2: cout << "\nValittu erotus ";
			break;
		case 3: cout << "\nValittu tulo ";
			break;
		default: cout << "\nVirhe: ei ko. toimintoa!"; // jos syotetty arvo ei vastaa yhtakaan numeroa valilla 0-3, tulostuu tama
		}
	} while (valinta != 0); // ajetaan loop uudestaan niin pitkaan kun kayttaja ei paina 0 valikossa

	return 0;
}

int KysyValinta(void) {
	int valinta;
	cout << "VALIKKO" << endl;
	cout << "0. Lopeta peli" << endl;
	cout << "1. Aloita yksinpeli" << endl;
	cout << "2. Aloita moninpeli" << endl;
	cout << "3. Tarkasta enn„tykset" << endl;
	cin >> valinta;
	return valinta;
}