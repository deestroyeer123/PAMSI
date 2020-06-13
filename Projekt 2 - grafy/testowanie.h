#pragma once
#ifndef _testowanie_h_
#define _testowanie_h_
#include <iostream>
#include <fstream>
#include "M_Graf.h"
#include "prim.h"
#include "kruskal.h"
#include <ctime>

using namespace std;

class Test {
private:
	float gestosc[4] = { 0.25, 0.50, 0.75, 1 };  //gestosci grafu: 25% 50% 75% i graf pelny
	int l_wierzch[5] = { 10, 50, 100, 500, 750};  //liczba wierzcholkow w grafie
	int l_krawedzi;
	double liczba_grafow = 100;   //liczba tworzonych grafow do testow (losowych instancji)
	double suma = 0;
	double srednia = 0;
	M_Graf g;
	Kruskal kr;
	Prim p;
	clock_t start, stop;
	double czas = 0;
public:
	void test(int reprezentacja, int algorytm);
};
#endif