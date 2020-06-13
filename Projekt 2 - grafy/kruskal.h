#pragma once
#ifndef _kruskal_h_
#define _kruskal_h_
#include "M_Graf.h"
#include "L_Graf.h"

using namespace std;

class Kruskal :public Tablice {
public:
	void kruskal(int *graf[], int l_wierzch, int l_krawedzi);
	void kruskal2(L_Graf* graf, int l_wierzch, int l_krawedzi);
	int find(int i);
	int uni(int i, int j);
};
#endif

