#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <queue>
#include <algorithm>

using namespace sf;
using namespace std;

queue<int> pozycjeO;
queue<int> pozycjeX;

const int rozmiar = 4;
const int ilosc_w_lini = 4;

void wyswietlenie_ukladu_planszy(int rozmiar)  //numeracja ukladu planszy do gry
{
	for (int i = 1; i <= (rozmiar*rozmiar); i++) {
		cout << " " << i << " ";
		if (i % rozmiar) {
			if (i <= 9)                   //estetyka planszy
				cout << " |";
			else
				cout << "|";
		}
		else {
			if (i != (rozmiar*rozmiar)) {
				cout << "\n----";
				for (int i = 1; i < rozmiar; i++) {
					cout << "+----";
				}
				cout << "\n";
			}
			else {
				cout << endl;
			}
		}
	}
}

void plansza(char t[], int rozmiar)          //pole gry 
{
	for (int i = 1; i <= (rozmiar*rozmiar); i++) {
		cout << " " << t[i] << " ";
		if (i % rozmiar) {
			cout << " |";
		}
		else {
			if (i != (rozmiar*rozmiar)) {
				cout << "\n----";
				for (int i = 1; i < rozmiar; i++) {
					cout << "+----";
				}
				cout << "\n";
			}
			else {
				cout << endl;
			}
		}
	}
}

bool win(char t[], char z, int rozmiar, int ilosc_w_lini)   //funkcja sprawdzajaca wygrana
{
	bool a = false, b = true;  //poczatkowa inicjalizacja zmiennych 

	for (int j = 1; j <= (rozmiar - ilosc_w_lini + 1); j++) {                             //wiersze 
		for (int i = j; i <= ((rozmiar * (rozmiar - 1)) + j); i += rozmiar) {
			b = true;         //inaczej po nieudanym sprawdzeniu b zawsze by bylo false
			for (int k = 0; k < ilosc_w_lini; k++) {
				b = b && (t[i + k] == z);       //sprawdzenie tych samych znakow w lini
			}
			a = a || b;     //wystarczy jedna wygrana linia
		}
	}

	for (int j = 1; j <= (rozmiar - ilosc_w_lini + 1); j++) {                   //kolumny 
		for (int i = ((j - 1) * rozmiar) + 1; i <= (j * rozmiar); i++) {
			b = true;              //inaczej po nieudanym sprawdzeniu b zawsze by bylo false
			for (int k = 0; k < ilosc_w_lini; k++) {
				b = b && (t[i + (rozmiar * k)] == z);          //sprawdzenie tych samych znakow w lini
			}
			a = a || b;             //wystarczy jedna wygrana linia
		}
	}

	for (int j = 1; j <= (rozmiar - ilosc_w_lini + 1); j++) {         //przekatne od lewego gornego rogu do prawego dolnego
		for (int i = j; i <= (rozmiar + j); i += rozmiar) {
			b = true;              //inaczej po nieudanym sprawdzeniu b zawsze by bylo false
			for (int k = 0; k < ilosc_w_lini; k++) {
				b = b && (t[i + ((rozmiar + 1) * k)] == z);          //sprawdzenie tych samych znakow w lini
			}
			a = a || b;            //wystarczy jedna wygrana linia
		}
	}

	for (int j = ((ilosc_w_lini - 1) * rozmiar) + 1; j <= (ilosc_w_lini * (rozmiar - 1)) + 1; j++) {         //przekatne od lewego dolnego rogu do prawego gornego
		for (int i = j; i <= (rozmiar + j); i += rozmiar) {
			b = true;                   //inaczej po nieudanym sprawdzeniu b zawsze by bylo false
			for (int k = 0; k < ilosc_w_lini; k++) {
				b = b && (t[i - ((rozmiar - 1) * k)] == z);         //sprawdzenie tych samych znakow w lini
			}
			a = a || b;              //wystarczy jedna wygrana linia
		}
	}
	if (a) return true;   //jak wygrana zwracamy true
	return false;
}


bool remis(char t[], int rozmiar)       //zwracamy true, gdy nie ma juz wolnych miejsc na planszy
{
	for (int i = 1; i <= (rozmiar*rozmiar); i++) if (t[i] == ' ') return false;
	return true;
}


int miejsca_wolne(char t[], int rozmiar)      //funkcja zwracajaca ilosc wolnych miejsc na planszy
{
	int mw = 0;
	for (int i = 1; i <= (rozmiar*rozmiar); i++) if (t[i] == ' ') mw++;
	return mw;
}


int poczatek(char t[], int rozmiar)     //funkcja losujaca pierwszy ruch komputera
{
	int pozycja;
	int zarodek = (int)time(NULL);
	srand(zarodek);
	do {
		pozycja = rand() % (rozmiar*rozmiar) + 1;
	} while ((t[pozycja] != ' '));
	Sleep(1000);
	return pozycja;
}

//algorytm mini-max, tablica t[] to plansza z aktualnymi pozycjami gracza
//char player przekazuje znak gracza (X lub O)
int minimax(char t[], char player, int poziom)
{
	int m = 0, mmx = 0;    //maksymalna wartosc ruchu wyliczona przez algorym, teoretyczna maksymalna wartosc ruchu
	int mw_min = (int)round(0.6 * rozmiar * rozmiar);
	int mw_max = rozmiar * rozmiar;
	int poziom_min1 = (int)round(0.5 * rozmiar * rozmiar * rozmiar / ilosc_w_lini);   //zmienna glebokosc drzewa
	int poziom_min2 = (int)round(0.5 * rozmiar * rozmiar * rozmiar / ilosc_w_lini);

	//sprawdzam ile jest wolnych miejsc na planszy
	int mw = miejsca_wolne(t, rozmiar);

	//sprawdzam czy ktos wygral lub jes remis
	if (win(t, player, rozmiar, ilosc_w_lini)) return (player == 'X') ? 1 : -1;//1 jesli komputer wygrywa, -1 jesli grajacy
	if (remis(t, rozmiar)) return 0;  //za remis 0

	if ((mw_min < mw) && (mw < mw_max)) {  //dla duzej ilosci miejsc wolnych
		if (poziom > poziom_min1) {  //ilosc anzlizowanych ruchow do przodu
			if (((player == 'O') && (m < mmx)) || ((player == 'X') && (m > mmx))) mmx = m;
			return mmx;
		}
	}
	else {  //dla mniejszej ilosci wolnych miejsc
		if (poziom > poziom_min2) {   //ilosc anzlizowanych ruchow do przodu
			if (((player == 'O') && (m < mmx)) || ((player == 'X') && (m > mmx))) mmx = m;
			return mmx;
		}
	}

	player = (player == 'X') ? 'O' : 'X';   //zmiana graczy w celu przeanalizowania ruchow
	mmx = (player == 'X') ? (-(rozmiar * rozmiar)) : (rozmiar * rozmiar);    //dla komputera max(mmx=-rozmiar^2), dla grajacego min(mmx=rozmiar^2)
	for (int i = 1; i <= rozmiar * rozmiar; i++) {    //w kazde pola na planszy
		if (t[i] == ' ') {           //ktore jest puste
			t[i] = player;         //wstawiamy znak odpowiedniego gracza
			m = minimax(t, player, poziom++);//i wyznaczamy wartosc tego ruchu rekurencyjnie
			t[i] = ' ';            //przywrocenie planszy do poprzedniego stanu
			if (((player == 'O') && (m < mmx)) || ((player == 'X') && (m > mmx))) mmx = m;
		}
	}
	return mmx;
}

//funkcja zwracajaca pozycje komputera obliczonÄ… algorytmem minimaxowym
int komputer(char t[])
{
	int pozycja, m, mmx;
	mmx = -(rozmiar * rozmiar);                  //max dla komputera
	for (int i = 1; i <= rozmiar * rozmiar; i++) {   //w kazde pole planszy
		if (t[i] == ' ') {       //ktore jest puste
			cout << ".";
			t[i] = 'X';          //wstawiamy znak komputera
			m = minimax(t, 'X', 0); //i wyznaczamy wartosc tej pozycji przez minimax
			t[i] = ' ';          //przywrocenie planszy do poprzedniego stanu
			if (m > mmx) {
				mmx = m;
				pozycja = i;
			}
		}
	}
	return pozycja;
}

//funkcja wstawiajaca X lub O do planszy, dla grajacego i komputera
void ruch(char t[], char &player, unsigned int licznik)
{
	int pozycja;
	if (player == 'O') { //jesli grajacy
		cout << endl << "Ruch gracza : ";
		cin >> pozycja;
		while ((pozycja < 1) || (pozycja > rozmiar * rozmiar)) {
			cout << "Wybiez pole z zakresu 1 - " << rozmiar * rozmiar << "! :";   //gdy poza zakresem
			cin >> pozycja;
			while (t[pozycja] != ' ') {
				cout << "To pole jest juz zajete! Wybierz inne : ";      //gdy zajete
				cin >> pozycja;
			}
		}
		while (t[pozycja] != ' ') {
			cout << "To pole jest juz zajete! Wybierz inne : ";          //gdy zajete
			cin >> pozycja;
			while ((pozycja < 1) || (pozycja > rozmiar * rozmiar)) {
				cout << "Wybiez pole z zakresu 1 - " << rozmiar * rozmiar << "! :";         //gdy poza zakresem
				cin >> pozycja;
			}
		}
		pozycjeO.push(pozycja);
	}
	else if (player == 'X') {  //jesli gra komputer

		if (licznik > 1)
			pozycja = komputer(t);           //pierwszy ruch
		else {
			pozycja = poczatek(t, rozmiar);    //kazdy kolejny
		}
		cout << endl << "Ruch komputera : " << pozycja << endl;
		pozycjeX.push(pozycja);
	}
	if ((pozycja >= 1) && (pozycja <= rozmiar * rozmiar) && (t[pozycja] == ' ')) t[pozycja] = player;
	else { cout << endl << "Cos poszlo nie tak" << endl; system("pause"); }
	player = (player == 'O') ? 'X' : 'O';   //zmiana gracza
}

void graficznie() {
	unsigned int licznik = 0;
	char t[rozmiar * rozmiar], player, wybor;
	RenderWindow window{ VideoMode{800,600}, "KOLKO I KRZYZYK" };    //okno graficzne o wybierach 800x600
	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	Texture tekstura1, tekstura2, tekstura3, tekstura4, tekstura5, tekstura6, tekstura7;
	tekstura1.loadFromFile("o.png");
	tekstura2.loadFromFile("x.png");
	tekstura3.loadFromFile("kreska.png");   //grafiki ladowane z pliku
	tekstura4.loadFromFile("kreska2.png");
	tekstura5.loadFromFile("wygrana.png");
	tekstura6.loadFromFile("przegrana.png");
	tekstura7.loadFromFile("remis.png");
	Sprite kolko, krzyzyk, kreska, kreska2, wygrana, przegrana, Remis;
	kolko.setTexture(tekstura1);
	krzyzyk.setTexture(tekstura2);
	kreska.setTexture(tekstura3);    //poinformawanie ktora tekstura ma byc rysowana
	kreska2.setTexture(tekstura4);
	wygrana.setTexture(tekstura5);
	przegrana.setTexture(tekstura6);
	Remis.setTexture(tekstura7);


	int pozycja_x = 0, pozycja_y = 0;   //wspolrzedne kolka wstawianego przez gracza
	Event event;         //zdarzenie
	int klikniete = 0;   //liczba klikniec przez gracza
	int pozycja;          //pozycja wpisywana do tablicy
	int rozmiar_kartki = 100;     //rozmiar jednej kratki
	player = 'O';                          //czlowiek zaczyna
	window.clear(Color(119, 136, 153));        //wyczyszczenie okna i ustwawienie koloru

	for (int i = 1; i <= rozmiar * rozmiar; i++) t[i] = ' ';   //zainicjowanie tablicy spacjami

	for (int i = 1; i <= (rozmiar - 1); i++) {
		for (int j = 1; j <= rozmiar; j++) {
			kreska.setPosition(((i - 1) * 100), ((j - 1) * 100));
			window.draw(kreska);
		}
	}                                                         //narysowanie planszy
	for (int i = 1; i <= (rozmiar - 1); i++) {
		for (int j = 1; j <= rozmiar; j++) {
			kreska2.setPosition(((j - 1) * 100), ((i - 1) * 100));
			window.draw(kreska2);
		}
	}

	while (window.isOpen()) {                   //kiedy okno otwarte
		Vector2i pozycjaMyszyWzgledemOkna = Mouse::getPosition(window);      //aktualna pozycja myszki

		while (window.isOpen() && !win(t, 'X', rozmiar, ilosc_w_lini) && !win(t, 'O', rozmiar, ilosc_w_lini) && !remis(t, rozmiar)) {
			pozycjaMyszyWzgledemOkna = Mouse::getPosition(window);

			while (window.pollEvent(event)) {          //gdy jakies zdarzenie

				if (event.type == Event::Closed) {
					window.close();
					break;
				}
				if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {  //kiedy puszczany lewy klawisz mysz (wybor pozycji kolka)
					int x = ((int)(rozmiar * pozycjaMyszyWzgledemOkna.x) / (rozmiar * rozmiar_kartki));
					int y = ((int)(rozmiar * pozycjaMyszyWzgledemOkna.y) / (rozmiar * rozmiar_kartki));
					//cout << "stawiam kolo w" << x * rozmiar_kartki << " " << y * rozmiar_kartki << "\n";
					kolko.setPosition(x*  rozmiar_kartki, y* rozmiar_kartki);
					window.draw(kolko);
					pozycja_x = x * rozmiar_kartki;
					pozycja_y = y * rozmiar_kartki;
					klikniete++;   //zliczanie klikniec
				}
			}
			if (klikniete > 0) {
				if ((klikniete % 2) != 0) {
					if (player == 'O') { //jesli grajacy

						int nr_kolumny = (pozycja_x / rozmiar_kartki) + 1;
						int nr_wiersza = (pozycja_y / rozmiar_kartki) + 1;
						pozycja = nr_kolumny + (rozmiar * (nr_wiersza - 1));

						while ((pozycja < 1) || (pozycja > rozmiar * rozmiar)) {
							cout << "Wybiez pole z zakresu 1 - " << rozmiar * rozmiar << "! :";

							while (t[pozycja] != ' ') {
								cout << "To pole jest juz zajete! Wybierz inne : ";

							}
						}
						while (t[pozycja] != ' ') {
							cout << "To pole jest juz zajete! Wybierz inne : ";

							while ((pozycja < 1) || (pozycja > rozmiar * rozmiar)) {
								cout << "Wybiez pole z zakresu 1 - " << rozmiar * rozmiar << "! :";

							}
						}

						pozycjeO.push(pozycja);
					}
				}
				else if (player == 'X') {  //jesli gra komputer

					if (licznik > 1) {
						pozycja = komputer(t);
						int nr_kolumny_k = ((pozycja % rozmiar) == 0) ? (rozmiar) : (pozycja % rozmiar);
						int nr_wiersza_k = ((pozycja % rozmiar) == 0) ? (pozycja / rozmiar) : ((int)(pozycja / rozmiar) + 1);
						krzyzyk.setPosition((nr_kolumny_k - 1) * 100, (nr_wiersza_k - 1) * 100);
					}
					else {
						pozycja = poczatek(t, rozmiar);
						int nr_kolumny_k = ((pozycja % rozmiar) == 0) ? (rozmiar) : (pozycja % rozmiar);
						int nr_wiersza_k = ((pozycja % rozmiar) == 0) ? (pozycja / rozmiar) : ((int)(pozycja / rozmiar) + 1);
						krzyzyk.setPosition((nr_kolumny_k - 1) * 100, (nr_wiersza_k - 1) * 100);
					}
					pozycjeX.push(pozycja);

				}
				if ((pozycja >= 1) && (pozycja <= rozmiar * rozmiar) && (t[pozycja] == ' ')) {
					t[pozycja] = player;
					if (player == 'X') {
						window.draw(krzyzyk);    //rysowanie krzyzyka przez komputer
					}
				}

				player = ((klikniete % 2) != 0) ? 'X' : 'O';   //zmiana gracza
				licznik++;
				if (player == 'X') klikniete++;

			}
			window.display();  //wyswietlania narysowanych rzeczy w oknie
		}
		//window.display();
		licznik = 0;

		if (win(t, 'X', rozmiar, ilosc_w_lini)) {
			przegrana.setPosition(400, 400);           //wygrana komputera
			window.draw(przegrana);
		}
		if (win(t, 'O', rozmiar, ilosc_w_lini)) {
			wygrana.setPosition(400, 400);            //wygrana gracza
			window.draw(wygrana);
		}
		if (remis(t, rozmiar)) {
			Remis.setPosition(400, 400);           //remis
			window.draw(Remis);
		}
		window.display();
	}
}

void konsolowo() {
	unsigned int licznik = 0;
	char t[rozmiar * rozmiar], player, wybor;

	do {
		for (int i = 1; i <= rozmiar * rozmiar; i++) t[i] = ' ';   //zainicjowanie tablicy spacjami
		player = 'O';                          //czlowiek zaczyna
		while (!win(t, 'X', rozmiar, ilosc_w_lini) && !win(t, 'O', rozmiar, ilosc_w_lini) && !remis(t, rozmiar)) {
			wyswietlenie_ukladu_planszy(rozmiar);
			cout << endl;
			plansza(t, rozmiar);
			ruch(t, player, licznik);
			licznik++;
			system("cls");
		}

		licznik = 0;
		plansza(t, rozmiar);
		if (win(t, 'X', rozmiar, ilosc_w_lini))       cout << endl << "Wygral komputer!" << endl;
		if (win(t, 'O', rozmiar, ilosc_w_lini))       cout << endl << "Wygrales!" << endl;
		if (remis(t, rozmiar))         cout << endl << "Remis!" << endl;

		cout << endl << "Czy chcesz zagrac jeszcze raz? (t = tak)"
			<< endl << "Wcisnij dowolny inny klawisz aby zakonczyc : ";
		cin >> wybor;
		cout << endl;
		system("cls");

	} while (wybor == 't');
}

int main()
{
	int wybor;
	cout << "Wybierz tryb gry: 1 - graficzny, 2 - konsolowy" << endl;
	cin >> wybor;
	switch (wybor)
	{
	case 1:
	{
		graficznie();  //gra z uzyciem sfmla
	}
	break;
	case 2:
	{
		system("cls");
		konsolowo();  //gra tylko na konsoli
	}
	break;
	default:
		break;
	}

	return 0;
}