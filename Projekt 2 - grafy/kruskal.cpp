#include "kruskal.h"
#include "M_Graf.h"

void swap(int* a, int* b) {      //zamiana elementu
	int temp = *a;
    *a = *b;
    *b = temp;
}

void sortuj(int* tab, int* srcTab, int* destTab, int n) {       //funkcja sortujaca wagi krawedzi
	for (int i = 0; i < n; i++) {       
       	for (int j = 0; j < n-i; j++)  {
       		if(tab[j] > tab[j+1]) {
       			swap(tab[j], tab[j+1]);
       			swap(srcTab[j], srcTab[j+1]);
       			swap(destTab[j], destTab[j+1]);
       		}
       	}
	}
}

void Kruskal::kruskal(int *graf[], int l_wierzch, int l_krawedzi) {   //algorytm Kruskala dla reprezentacji macierzowej
	int a=0, b=0, u=0, v=0;
	int waga = 0;
	int k = 0;
	int inf = 999999;  //nieskonczonosc

	int krawedziePosortowane[l_krawedzi];
	int srcTab[l_krawedzi];
	int destTab[l_krawedzi];
	int index = 0; 
	for (int i = 0; i < l_wierzch; i++) {
		for (int j = i + 1; j < l_wierzch; j++) {
			krawedziePosortowane[index] = graf[i][j];
			srcTab[index] = i;
			destTab[index] = j;
			index++;
		}
	}

	sortuj(krawedziePosortowane, srcTab, destTab, l_wierzch);

	int minimalne_drzewo_rozpinajace[l_wierzch][l_wierzch];
	bool czy_odwiedzone[l_wierzch];

	for(int i = 0; i < l_wierzch; i++)
		for(int j = 0; j < l_wierzch; j++)
			minimalne_drzewo_rozpinajace[i][j] = 0;

	for(int i = 0; i < l_wierzch; i++)
		czy_odwiedzone[i] = false;

	index = 0;
	while (k++ < l_wierzch - 1) {
		if(odwiedzone[destTab[index]] == true && krawedziePosortowane[index] != 0) //jezeli odwiedzone to nastepna krawedz
			index++;

		minimalne_drzewo_rozpinajace[srcTab[index]][destTab[index]] = krawedziePosortowane[index];
		minimalne_drzewo_rozpinajace[destTab[index]][srcTab[index]] = krawedziePosortowane[index];
		czy_odwiedzone[srcTab[index]] = true;
		czy_odwiedzone[destTab[index]] = true;		
	}

	for(int i = 0; i < l_wierzch; i++)
		for(int j = 0; j < l_wierzch; j++)
			graf[i][j] = minimalne_drzewo_rozpinajace[i][j];
}


void Kruskal::kruskal2(L_Graf* graf, int l_wierzch, int l_krawedzi) {      //algorytm Kruskala dla reprezentacji listowej

	int a = 0, b = 0, u = 0, v = 0;
	int waga = 0;
	int k = 0;
	int inf = 999999;  //nieskonczonosc
	int min = inf;
	int krawedziePosortowane[l_krawedzi];
	int srcTab[l_krawedzi];
	int destTab[l_krawedzi];
	int index = 0; 
	for (int i = 0; i < l_wierzch; i++) {
		Krawedz* e = graf->wezKrawedz(i);
		while (e->dest != -1) {
			krawedziePosortowane[index] = e->waga;
			srcTab[index] = i;
			destTab[index] = e->dest;
			index++;
			e = e->nast;
		}
	}
	

	sortuj(krawedziePosortowane, srcTab, destTab, l_wierzch);

	L_Graf* graf_pom = new L_Graf(l_wierzch);
	bool czy_odwiedzone[l_wierzch];

	index = 0;
	while (k++ < l_wierzch - 1) {
		if(odwiedzone[destTab[index]] == true && krawedziePosortowane[index] != 0) //jezeli odwiedzone to nastepna krawedz
			index++;

		graf_pom->wezKrawedz(srcTab[index])->dodajWierzcholek(destTab[index], krawedziePosortowane[index]);
		graf_pom->wezKrawedz(destTab[index])->dodajWierzcholek(srcTab[index], krawedziePosortowane[index]);
		czy_odwiedzone[srcTab[index]] = true;
		czy_odwiedzone[destTab[index]] = true;		
	}

	delete graf_pom;
	//return graf_pom;

	//cout << l_wierzch << " " << l_krawedzi << endl;	
	
}

int Kruskal::find(int i) {
	while (parent[i])
		i = parent[i];
	return i;
}

int Kruskal::uni(int i, int j) {
	if (i != j) {
		parent[j] = i;
		return 1;
	}
	return 0;
}
