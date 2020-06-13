#pragma once
#ifndef _Lista_h_
#define _Lista_h_
#include <iostream>
#include <fstream>

using namespace std;

struct Graf    //struktura grafu przechowujaca wierzcholki i krawedzie
{
	int V, E;

	struct Krawedz* krawedz;

};


struct Krawedz {   //struktura krawedzi
	Krawedz();
	int dest;
	double waga;
	Krawedz* nast;
	void dodajWierzcholek(int dest, double waga);
	void wypiszKrawedzie();
};



struct Element {
	double waga;
	int dest = -1;
	int src = -1;
	Element* nast = NULL;
};

struct Lista {          //struktura listy
	int iloscElem = 0;
	Element* head = NULL;
	void dodajElement(int src, int dest, double waga);	
	void wyswietl();
	void usun(int n);
	~Lista();
};
#endif