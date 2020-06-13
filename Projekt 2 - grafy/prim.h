#pragma once
#ifndef _prim_h_
#define _prim_h_
#include "M_Graf.h"
#include "L_Graf.h"

using namespace std;

class Prim :public Tablice {
public:
	void prim(int *graf[], int l_wierzch, int l_krawedzi);
	L_Graf* prim2(L_Graf* graf, int l_wierzch, int l_krawedzi);
};
#endif
