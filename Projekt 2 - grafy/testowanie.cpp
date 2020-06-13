#include "M_Graf.h"
#include "testowanie.h"
#include "L_Graf.h"

using namespace std;


void Test::test(int reprezentacja, int algorytm) {

	//string nazwa[] = {"0_0.txt", "0_1.txt","1_0.txt","1_1.txt"};
	//fstream wyniki(nazwa[reprezentacja * 2 + algorytm], ios::app);
	
	fstream wyniki("Wyniki_macierz.txt", ios::app);
	fstream wyniki2("Wyniki_lista.txt", ios::app);

	switch (reprezentacja) {
	case 0:
	{
		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 5; i++) {

				for (int k = 1; k <= liczba_grafow; k++) {

					int l_krawedzi = gestosc[j] * l_wierzch[i] * (l_wierzch[i] - 1) / 2;

					int **tab3 = new int *[l_wierzch[i]];
					for (int w = 0; w < l_wierzch[i]; w++)
						tab3[w] = new int[l_krawedzi];

					g.stworz(tab3, l_wierzch[i], l_krawedzi);

					switch (algorytm) {
					case 0:
					{
						start = clock();
						kr.kruskal(tab3, l_wierzch[i], l_krawedzi);  //kruskal dla macierzy
						stop = clock();
					}
					break;
					case 1:
					{
						start = clock();
						p.prim(tab3, l_wierzch[i], l_krawedzi);  //prime dla macierzy
						stop = clock();
					}
					break;

					default:
						break;
					}
					czas = (stop - start) / (double)CLOCKS_PER_SEC;
					suma += czas;

					for (int w = 0; w < l_wierzch[i]; w++)
						delete[] tab3[w];
					delete[]tab3;
				}
				srednia = suma / liczba_grafow;
				wyniki << "srednia: " << gestosc[j] << "  " << l_wierzch[i] << "  ";
				wyniki.setf(ios::fixed);
				wyniki.precision(8);
				wyniki << srednia << " sekund" << endl;
				wyniki.precision(2);
				suma = 0;
			}

		}
	}
	break;
	case 1:
	{					

		for (int j = 0; j < 4; j++) {
			for (int i = 0; i < 5; i++) {
				for (int k = 1; k <= liczba_grafow; k++) {

					int l_krawedzi = gestosc[j] * l_wierzch[i] * (l_wierzch[i] - 1) / 2;

					L_Graf* graf = new L_Graf(l_wierzch[i]);
					
					graf->stworzGraf(gestosc[j]);
					
					switch (algorytm) {
					case 0:
					{	
						start = clock();
						kr.kruskal2(graf, graf->wezV(), graf->wezE());    //kruskal dla listy
						stop = clock();
					}
					break;
					case 1:
					{
						start = clock();
						p.prim2(graf, graf->wezV(), graf->wezE());    //prime dla listy
						stop = clock();
					}
					break;

					default:
						break;
					}
					czas = (stop - start) / (double)CLOCKS_PER_SEC;
					suma += czas;
					delete graf;
				}
				srednia = suma / liczba_grafow;
				wyniki2 << "srednia: " << gestosc[j] << "  " << l_wierzch[i] << "  ";
				wyniki2.setf(ios::fixed);
				wyniki2.precision(8);
				wyniki2 << srednia << " sekund" << endl;
				wyniki2.precision(2);
				suma = 0;
			}
		}					

	}
	break;
	default:
		break;
	}

}
