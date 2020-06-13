#pragma once
#ifndef _L_Graf_h_
#define _L_Graf_h_
#include <iostream>
#include <fstream>

#include "Lista.h"

using namespace std;


class L_Graf {
private:
	struct Graf* graf;

public:
	L_Graf(int V);
	~L_Graf();
	void dodajKrawedz(int source, int dest, double weight);
	void wypiszKrawedzie();
	void stworzGraf(double Density);
	void wczytajGraf();
	inline int wezV() { return graf->V; }
	inline int wezE() { return graf->E; }
	inline Krawedz* wezKrawedz(int i) { return &graf->krawedz[i]; }
};
#endif