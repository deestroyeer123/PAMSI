#pragma once
#ifndef _M_Graf_h_
#define _M_Graf_h_
#include <iostream>
#include <fstream>


using namespace std;


class Tablice {
public:
	int odwiedzone[1000] = { 0 };
	int parent[1000] = { 0 };
};

class M_Graf {
public:
	
	void wyswietl(int *graf[], int l_wierzch);
	void zapisz(int *graf[], int l_wierzch);
	void wczytaj(int *graf[], int l_wierzch);
	void stworz(int *graf[], int l_wierzch, int l_krawedzi);
	
};
#endif

