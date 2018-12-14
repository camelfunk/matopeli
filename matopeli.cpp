#include <iostream>
using namespace std;
#include <windows.h>
#include <conio.h> 
void KysyValinta();
void Asetukset();
void AloitaPeli();
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

// h�nn�n koordinaatit
int hanta_x[100], hanta_y[100]; // hantax [10, 10, 9, 8 ,8]  Ooo
								// hantay [ 2, 3, 2 , 2 ,3
int hanta_pituus;

// liikuminen
enum SUUNTA { ALKU = 0, OIKEALLE, ALAS, VASEMMALLE, YLOS };
SUUNTA suunta;

int pisteet = 0;

bool seinat = false; //voiko k�yd� seinien l�pi
bool multiplayer = false;
int pelaaja;
int pisteet2;

int main()
{
	ShowConsoleCursor(false); // ei haluta, ett� kursori n�kyy ruudussa
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
		cout << "3. Asetukset" << endl;
		cin >> valinta;
		
		switch (valinta) // valitsee casen valinnan saaman arvon mukaisesti
		{
		case 0:
			cout << "Peli suljetaan" << endl;
			exit(0); //suljetaan peli
		case 1:
			cout << "\nValittu yksinpeli" << endl;
			multiplayer = false;
			AloitaPeli(); 
			break; // break poistuu switch-lauseesta seuraavaan
		case 2: cout << "\nValittu moninpeli " << endl;
			multiplayer = true;
			pelaaja = 1;
			AloitaPeli();
			break;
		case 3: cout << "\nValittu Asetukset" << endl;
			Asetukset();
			break;
		default: cout << "\nVirhe: ei ko. toimintoa!"; // jos syotetty arvo ei vastaa yhtakaan numeroa valilla 0-3, tulostuu tama
		}
	} while (valinta != 0); // ajetaan loop uudestaan niin pitkaan kun kayttaja ei paina 0 valikossa

}

void Asetukset() {
	system("cls");
	int valinta;
	cout << "ASETUKSET" << endl;
	cout << "1. Pelaa seinien kanssa" << endl;
	cout << "2. Pelaa ilman seini�" << endl;
	cin >> valinta;

	switch (valinta)
	{
	case 1:
		seinat = true;
		KysyValinta();
		break;
	case 2: 
		seinat = false;
		KysyValinta();
		break;
	default: KysyValinta();
	}
}

void AloitaPeli() {
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
		system("cls"); // puhdistetaan n�ytt�

		// piirret��n ruutu
		for (int i = 0; i <= leveys; i++)
		{
			cout << "-";	// yl�rivi
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
					cout << "O"; // piirret��n madon p��
				}
				else if (i == omena_y && j == omena_x) {
					cout << "x"; // piirret��n omena
				}
				else {

					bool onkoHanta = false;
					for (int k = 0; k < hanta_pituus; k++)
					{
						if (hanta_x[k] == j && hanta_y[k] == i)
						{
							cout << "o"; // piirret��n madon h�nt��
							onkoHanta = true;
						}

					}
					if (!onkoHanta)
						cout << " ";	// mik�li paikassa ei ole h�nt��, piirret��n tyhj� v�li
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
		case 'q':
			LopetaPeli();
			break;
		}
	}
}

void Liiku() {
															
	//h�nn�n liikuminen
	int seuraava_x = hanta_x[0];	
	int seuraava_y = hanta_y[0];	
	hanta_x[0] = mato_x;	// h�nt� siirtyy madon p��n tilalle    Ooooo
	hanta_y[0] = mato_y;
	int temp_x, temp_y;

	// siiret��n koordinati-taulukkojen alkiot yksi taaksep�in
	for (int i = 1; i < hanta_pituus; i++)
	{
		temp_x = hanta_x[i];	
		temp_y = hanta_y[i];	
		hanta_x[i] = seuraava_x; 
		hanta_y[i] = seuraava_y; 
		seuraava_x = temp_x;	
		seuraava_y = temp_y;
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
	if (mato_x >= leveys || mato_x <= 0 || mato_y >= korkeus || mato_y < 0) { // kun t�rm�t��n sein��n
		if (seinat) LopetaPeli();
		else if (mato_x >= leveys) mato_x = 0;
		else if (mato_x <= 0) mato_x = leveys - 1;
		else if (mato_y >= korkeus) mato_y = 0;
		else if (mato_y < 0) mato_y = korkeus - 1;
	}

	for (int i = 0; i < hanta_pituus; i++) // tai kun torm�t��n h�nt��n
	{
		if (hanta_x[i] == mato_x && hanta_y[i] == mato_y)
			LopetaPeli();
	} 

	if (mato_x == omena_x && mato_y == omena_y) {	// kun omena on sy�ty
		pisteet++;
		omena_x = rand() % 20;
		omena_y = rand() % 20;
		hanta_pituus++;
	}
}

void LopetaPeli() {
	system("cls");
	mato_x = leveys / 2;	//Asetetaan kaikki takaisin alkuun
	mato_y = korkeus / 2;
	suunta = ALKU;
	hanta_pituus = 0;
	if (multiplayer) {
		switch (pelaaja)
		{
		case 1: pisteet2 = pisteet;
			pelaaja++;
			pisteet = 0;
			AloitaPeli();
			break;
		case 2:
			if (pisteet2 > pisteet) cout << "Ensimm�inen pelaaja voitti." << endl << endl;
			else if (pisteet2 < pisteet) cout << "Toinen pelaaja voitti" << endl << endl;
			else cout << "Tasapeli!" << endl << endl;
			pelaaja = 0;
			pisteet = 0;
			KysyValinta();
			break;
		default:
			break;
		}
	}
	
	cout << "GAME OVER" << endl << endl;
	cout << "Sait " << pisteet << " pistett�!" << endl << endl;
	pisteet = 0;
	KysyValinta();
}

void ShowConsoleCursor(bool showFlag) //ettei kursori vilkkuisi n�yt�ll�
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; //kursori n�kym�tt�m�ksi
		SetConsoleCursorInfo(out, &cursorInfo);
	}