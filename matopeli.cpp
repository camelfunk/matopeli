#include <iostream>
using namespace std;
#include <windows.h>
#include <conio.h> 
void KysyValinta();
void AloitaPeli(int);
void LuoKartta();
void Syotto();
void Liiku();
void LopetaPeli();
void ShowConsoleCursor(bool showFlag);

// ruutu
const int leveys = 20; // x
const int korkeus = 20; // y

// omena ilmestyy satunnaiseen paikkaan
int omena_x = rand() % 20;
int omena_y = rand() % 20;

// mato alussa ilmestyy ruudun keskelle
int mato_x = leveys / 2;
int mato_y = korkeus / 2;

// hännän koordinaatit
int hanta_x[100], hanta_y[100];
int hanta_pituus;

// liikuminen
enum SUUNTA { ALKU = 0, OIKEALLE, ALAS, VASEMMALLE, YLOS };
SUUNTA suunta;

int pisteet = 0;

int main()
{
	ShowConsoleCursor(false); // ei haluta, että kursori näkyy ruudussa
	KysyValinta();

	return 0;
}

void KysyValinta() {
	int valinta;
	
	do // ajetaan loop lapi ainakin kerran
	{
		cout << "VALIKKO" << endl;
		cout << "0. Lopeta peli" << endl;
		cout << "1. Aloita yksinpeli" << endl;
		cout << "2. Aloita moninpeli" << endl;
		cout << "3. Tarkasta enn„tykset" << endl;
		cout << "4. Asetukset" << endl;
		cin >> valinta;
		
		switch (valinta) // valitsee casen valinnan saaman arvon mukaisesti
		{
		case 0:
			cout << "Peli suljetaan" << endl;
			exit(0); //suljetaan peli
		case 1:
			cout << "\nValittu yksinpeli" << endl;
			AloitaPeli(1); 
			break; // break poistuu switch-lauseesta seuraavaan
		case 2: cout << "\nValittu monipeli " << endl;
			AloitaPeli(2);
			break;
		case 3: cout << "\nValittu ennätykset " << endl;
			break;
		case 4: cout << "\nValittu Asetukset" << endl;
			break;
		default: cout << "\nVirhe: ei ko. toimintoa!"; // jos syotetty arvo ei vastaa yhtakaan numeroa valilla 0-3, tulostuu tama
		}
	} while (valinta != 0); // ajetaan loop uudestaan niin pitkaan kun kayttaja ei paina 0 valikossa

}

void AloitaPeli(int pelaajia) {
	while (true)
	{
		LuoKartta();
		Syotto();
		Liiku();
		Sleep(30);
	}
	return;
}

void LuoKartta() {
		system("cls"); // puhdistetaan näyttö

		// piiretään ruutu
		for (int i = 0; i <= leveys; i++)
		{
			cout << "-";	// ylärivi
		}
		cout << endl;

		for (int i = 0; i < korkeus; i++)
		{
			for (int j = 0; j <= leveys; j++)
			{
				if (j == 0 || j == leveys)
				{
					cout << "I";
				}
				else if (i == mato_y && j == mato_x) {
					cout << "O"; // piiretään mato
				}
				else if (i == omena_y && j == omena_x) {
					cout << "x"; // piiretään omena
				}
				else {

					bool print = false;
					for (int k = 0; k < hanta_pituus; k++)
					{
						if (hanta_x[k] == j && hanta_y[k] == i)
						{
							cout << "o";
							print = true;
						}

					}
					if (!print)
						cout << " ";
				}
				
			}
			cout << endl;
		}
		for (int i = 0; i <= leveys; i++)
		{
			cout << "-"; // alarivi
		}
		cout << endl << endl;
		cout << "Pisteet: " << pisteet;
		
}

void Syotto() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'w':
			suunta = YLOS;
			break;
		case 'd':
			suunta = OIKEALLE;
			break;
		case 'a':
			suunta = VASEMMALLE;
			break;
		case 's':
			suunta = ALAS;
			break;
		}
	}
}

void Liiku() {

	//hännän liikuminen
	int prevX = hanta_x[0];
	int prevY = hanta_y[0];
	int prev2x, prev2y;
	hanta_x[0] = mato_x;
	hanta_y[0] = mato_y;

	for (int i = 1; i < hanta_pituus; i++)
	{
		prev2x = hanta_x[i];
		prev2y = hanta_y[i];
		hanta_x[i] = prevX;
		hanta_y[i] = prevY;
		prevX = prev2x;
		prevY = prev2y;
	}

	switch (suunta)
	{
	case YLOS:
		mato_y--;
		break;
	case OIKEALLE:
		mato_x++;
		break;
	case VASEMMALLE:
		mato_x--;
		break;
	case ALAS:
		mato_y++;
		break;
	}
	if (mato_x > leveys || mato_x < 0 || mato_y > korkeus + 1 || mato_y < 0)
		LopetaPeli();
	if (mato_x == omena_x && mato_y == omena_y) {
		pisteet++;
		omena_x = rand() % 20;
		omena_y = rand() % 20;
		hanta_pituus++;
	}
}

void LopetaPeli() {
	system("cls");
	cout << "GAME OVER" << endl << endl;
	cout << "Sait " << pisteet << " pistettä!" << endl << endl;
	mato_x = leveys / 2;
	mato_y = korkeus / 2;
	suunta = ALKU;
	hanta_pituus = 0;
	KysyValinta();
}

void ShowConsoleCursor(bool showFlag) //ettei kursori vilkkuisi näytöllä
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; //kursori näkymättömäksi
		SetConsoleCursorInfo(out, &cursorInfo);
	}