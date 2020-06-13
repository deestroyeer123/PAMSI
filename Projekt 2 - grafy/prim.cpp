#include "prim.h"
#include "M_Graf.h"
#include "Lista.h"

void Prim::prim(int *graf[], int l_wierzch, int l_krawedzi) {      //algorytm prima dla reprezenacji macierzowej
	int a=0, b=0, u=0, v=0;
	int waga = 0;
	int min;
	int index;
	int index_2;
	int k = 0;
	int inf = 999999;  //nieskonczonosc

	odwiedzone[0] = 1;	
	Lista* lista = new Lista;
	Element* head = lista->head;

	for(int i = 0; i < l_wierzch; i++)
		if(graf[0][i] != 0)
			lista->dodajElement(0, i, graf[0][i]);

	int tab[l_wierzch][l_wierzch];
	for (int i = 0; i < l_wierzch; i++)
		for (int j = 0; j < l_wierzch; j++)
			tab[i][j] = 0;


	while (k++ < l_wierzch - 1) {
		min = inf;

		Element* l = lista->head;	//Wyznaczenie krawedzi o najmniejszej wadze z dostepnych (wychodzacych z odwiedzonych wierzcholkow)

		while (l != NULL) {
			if(min > l->waga) {
				min = l->waga;
				u = l->src;
				v = l->dest;
			}
			l = l->nast;
		}	

		tab[u][v] = min;
		tab[v][u] = min;
		odwiedzone[v] = 1;

		l = lista->head;
		Element *l2 = lista->head;
		int nr = 0;
		while (l != NULL) {
			l2 = l->nast;
			if(l->dest == v) {
				lista->usun(nr);
				nr--;
			}
			l = l2;
			nr++;
		}
		for(int i = 0; i < l_wierzch; i++)
			if(graf[v][i] != 0 && !odwiedzone[i])
				lista->dodajElement(v, i, graf[v][i]);


	}
	//cout<<"Suma: "<<waga<<endl;
	for (int i = 0; i < l_wierzch; i++)
		odwiedzone[i] = 0;

	for (int i = 0; i < l_wierzch; i++) {
		for (int j = 0; j < l_wierzch; j++) {
			graf[i][j] = tab[i][j];
		}
	}
}


L_Graf* Prim::prim2(L_Graf* graf, int l_wierzch, int l_krawedzi) {          //algorytm prima dla postaci listowej
	int a=0, b=0, u=0, v=0;
	int waga = 0;
	double min;
	int k = 0;
	int inf = 999999;  //nieskonczonosc


	L_Graf* graf_pom = new L_Graf(l_wierzch);
	Lista* lista = new Lista;
	Element* head = lista->head;

	odwiedzone[0] = 1;
	Krawedz *e = graf->wezKrawedz(0);
	while (e->dest != -1) {
		lista->dodajElement(0, e->dest, e->waga);
		e = e->nast;
	}	

	Element *el = lista->head;


	while (k++ < l_wierzch - 1) {
		//cout << k << " " << l_wierzch -1 << endl;
		min = inf;	

		Element *l = lista->head;
		while (l != NULL) {
			if(l->dest == -1)
				break;
			if(min > l->waga) {
				min = l->waga;
				u = l->src;
				v = l->dest;
			}

			l = l->nast;
		}	
		//cout << u << " " << v << " " << min << endl;
		graf_pom->dodajKrawedz(u, v, min);
		graf_pom->dodajKrawedz(v, u, min);
		odwiedzone[v] = 1;

		l = lista->head;
		Element *l2 = lista->head;
		int nr = 0;
		while (l != NULL) {
			l2 = l->nast;
			if(l->dest == v) {
				lista->usun(nr);
				nr--;
			}
			l = l2;
			nr++;
		}
		e = graf->wezKrawedz(v);
		while (e->dest != -1) {
			if(!odwiedzone[e->dest])
				lista->dodajElement(v, e->dest, e->waga);
			e = e->nast;
		}
	}
	delete lista;

	return graf_pom;	
}
