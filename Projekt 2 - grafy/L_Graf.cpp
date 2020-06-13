#include "L_Graf.h"
#include "Lista.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>


using namespace std;


void L_Graf::wczytajGraf() {               //wczytywaine grafu w postaci listowej z pliku
	ifstream plik;
	int waga;
	
	plik.open("input.txt", ios::in);
	for(int i = 0; i < graf->V; i++) {
		for(int j = 0; j < graf->V; j++) {
			plik >> waga;
			if(waga != 0) {
				dodajKrawedz(i, j, waga);
			}
		}
	}

	plik.close();
}

L_Graf::~L_Graf() {                       //destruktor dla L_Graf (lista)
	for(int V = 0; V < graf->V; V++) {
		Krawedz* edges[graf->V];
		Krawedz* edge = &graf->krawedz[V];
		int i = -1;
		while(edge->dest != -1) {
			edge = edge->nast;
			edges[++i] = edge;
		}
		for(; i >= 0; i--)
			delete edges[i];
	}

	delete[] graf->krawedz;
	delete graf;
}

L_Graf::L_Graf(int V) {               //konstruktor dla L_Graf (lista)
	graf = new Graf;
	graf->V = V;
	graf->E = 0;	
	graf->krawedz = new Krawedz[V];
	for(int i = 0; i < V; i++) {
		graf->krawedz[i] = Krawedz();
	}
}

void L_Graf::dodajKrawedz(int source, int dest, double weight) {        //dodawanie krawedzi o wadze, koncu i poczatku
	graf->E++;
	graf->krawedz[source].dodajWierzcholek(dest, weight);
}

void L_Graf::wypiszKrawedzie() {                 //wyswietlenie krawedzi
	cout << "Print Edges" << endl;
	int V = graf->V;
	for (int i = 0; i < V; i++) {
		graf->krawedz[i].wypiszKrawedzie();
		cout << endl;
	}
}


void L_Graf::stworzGraf(double Density) {             //stworzenie losowego grafu w postaci listowej o okreslonej gestosci
	int V = graf->V;
	int source = 0;
	int dest = 0;
	double weight = 0;

	int E = (int)(Density * V * (V - 1)) / 2;   //obliczenie ilosci krawedzi

	
	for (int i = 0; i < E; i++) {
		do {
			source = rand() % V;
			dest = rand() % V;
			weight = rand() % 20;
		} while(source == dest);

		dodajKrawedz(source, dest, weight);
	}
}
