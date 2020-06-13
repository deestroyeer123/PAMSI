#include "M_Graf.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
using namespace std;


void M_Graf::wyswietl(int *graf[], int l_wierzch) {          //wyswietlenie grafu w postaci macierzowej
	
	for (int i = 0; i < l_wierzch; i++) {
		for (int j = 0; j < l_wierzch; j++)
			cout << graf[j][i] << " ";
		cout << endl;
	}
}

void M_Graf::zapisz(int *graf[], int l_wierzch) {             //zapisanie grafu w postaci macierzowej z pliku
	fstream plik;
	plik.open("graf_zapisany.txt", ios::out);
	for (int i = 0; i < l_wierzch; i++) {
		for (int j = 0; j < l_wierzch; j++)
			plik << graf[j][i] << " ";
		plik << endl;
	}
	plik.flush();
	plik.close();
}

void M_Graf::wczytaj(int *graf[], int l_wierzch) {           //wczytywaine grafu w postaci macierzowej z pliku
	ifstream plik;
	plik.open("graf.txt", ios::in);
	//cout << "elko";
	for (int i = 0; i < l_wierzch; i++) {
		for (int j = 0; j < l_wierzch; j++)
			plik >> graf[j][i];
	}
	plik.close();
}

void M_Graf::stworz(int *graf[], int l_wierzch, int l_krawedzi) {        //stworzenie losowego grafu w postaci macierzowej o okreslonej ilosci wierzcholkow i krawedzi
	if (l_krawedzi > (l_wierzch*(l_wierzch - 1) / 2)) {                         //graf ponad pelny
		cout << "za duzo krawedzi!, gestosc grafu ponad 100 procent" << endl;
		return;
	}

	for (int i = 0; i < l_wierzch; i++) {       //poczatkowy graf w postaci macierzy wypelniony zerami
		for (int j = 0; j < l_wierzch; j++)
			graf[j][i] = 0;
	}
	
	for (int i = 0; i < l_krawedzi;) {
		int waga = rand() % 9 + 1;      //losowanie wagi krawedzi
		int w1 = rand() % l_wierzch;    //losowanie poczatku krawedzi (pierwszy wierzcholek)
		int w2 = rand() % l_wierzch;     //losowanie konca krawedzi  (drugi wierzcholek)
	
		if (graf[w1][w2] == 0 && w1 != w2) {    
			graf[w1][w2] = waga;
			graf[w2][w1] = waga;
			i++;  //iteracja dopiero jak dodamy krawedz
		}
	}
}










