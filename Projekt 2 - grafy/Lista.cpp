#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <fstream>

#include "Lista.h"


using namespace std;

Krawedz::Krawedz() {                 //konstruktor krawedzi
	dest = -1;
	waga = 0;
	nast = NULL;
}



void Krawedz::dodajWierzcholek(int dest, double waga) {
	Krawedz* edge = this;
	while (edge->dest != -1) {   //dojscie do konca listy
		edge = edge->nast;
	}
	
	edge->dest = dest;
	edge->waga = waga;
	edge->nast = new Krawedz;
}

void Krawedz::wypiszKrawedzie() {    //wypisanie krawedzi
	Krawedz *e = this;
	while (e->dest != -1) {
		cout << e->dest << " ";
		e = e->nast;
	}
}

void Lista::dodajElement(int src, int dest, double waga) {    //dodanie elementu o okreslonej wadze, koncu i poczatku
	Element* el = new Element;

	el->waga = waga;
	el->dest = dest;
	el->src = src;


	if(iloscElem == 0) {
		head = el;
	}
	else {
		el->nast = head->nast;
		head->nast = el;
	}
	iloscElem++;
}

void Lista::wyswietl() {
	Element *l = head;
	while(l != NULL) {
		cout << l->src << " " << l->dest << " " << l->waga << endl;
		l = l->nast;
	}
	cout << endl;
}


void Lista::usun(int n) {
	Element* l = head;
	int num = 0;
	while(l != NULL) {
		num++;
		l = l->nast;
	}


	if(n > iloscElem)
		return;
	Element* toDel;
	if(n == 0) {
		Element* temp = head;
		toDel = head;
		head = temp->nast;
	}
	else {
		Element* l = head;
		int nr = 0;

		while(l != NULL) {
			if(nr == n-1)
				break;
			nr++;
			l = l->nast;
		}

		toDel = l->nast;
		
		if(toDel->nast == NULL) {
			l->nast = NULL;
		}
		else
			l->nast = toDel->nast;
		
	}
	
	delete toDel;

	iloscElem--;
}



Lista::~Lista() {                      //destruktor listy
	Element* l = this->head;
	Element* l2 = this->head;
	while(l != NULL) {
		l2 = l->nast;
		delete l;
		l = l2;
	}
}
