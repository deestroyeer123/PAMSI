//#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

int n;  //rozmiar tablicy

template <typename T>
void show_tab(T *tab, int first = 0, int last = n - 1) {
	for (int i = first; i <= last; i++) {
		cout << tab[i] << " ";
	}
}

template <typename T>
void losuj_tab(T *tab, int rozmiar, int zakres, double procent) {
	int index_los = rozmiar - (rozmiar * ((100 - procent) / 100));
	if (procent != 0) {
		for (int i = 0; i < index_los; i++) {
			tab[i] = i;
		}
	}
	if (procent != 100) {
		for (int i = index_los; i < rozmiar; i++) {
			if (index_los == 0) {
				tab[i] = rand() % zakres;
			}
			else
			{
				tab[i] = (rand() % (zakres - index_los + 2)) + tab[index_los - 1];
			}
		}
	}
}

template <typename T>
void odwroc_tab(T *tab, int rozmiar) {
	for (int i = 0; i < rozmiar; i++) {
		tab[i] = rozmiar - i;
	}
}

template <typename T>
void swap(T *tab, int first, int second) {
	int temp = tab[second];
	tab[second] = tab[first];
	tab[first] = temp;
}

template <typename T>
class QuickSort {
private:
	void quickSort(T *tab, int left, int right) {
		//cout << "lewy: " << left << endl << "prawy: " << right << endl;
		
		if (left >= right) {      //gdy mamy tylko jeden element
			return;
		}
		int pivot = tab[right];  //pivot jako ostatni element
		int granica = left - 1;  //granica na wstepie na poczatku tablicy 
		int licznik = left;      //licznik do przemieszczania sie po tablicy
		while (licznik < right) {  //poruszanie sie po calej tablicy
			if (tab[licznik] < pivot) {
				granica++;           //gdy element mniejszy od pivota przesuwamy granice i zamieniamy ja z elementem (unikamy zamiany elementu z samym soba)
				if (granica != licznik) {
					//cout << endl << "granica: " << granica << endl;
					swap(tab, granica, licznik);
					//cout << "granica: " << granica << endl;
				}
			}
			licznik++;
		}
		granica++;               //ustawienie pivota w odpowiednim miejscu sztucznie przesuwajac granice (unikamy zamiany pivota z samym soba)
		if (granica != right) {
			swap(tab, granica, right);
		}
		
		quickSort(tab, left, granica - 1); //wykonanie rekurencyjne dla lewej czesci
		quickSort(tab, granica + 1, right); //dla prawej
	
	}
public:
	void sort(T *tab_to_sort, int rozmiar) {
		if (tab_to_sort == NULL || rozmiar == 0) {
			return;
		}
		int n = rozmiar;
	
		quickSort(tab_to_sort, 0, rozmiar - 1);
		
	}
};

template <typename T>
class MergeSort {
private:
	T *temp_tab;
	void merge(T *tab, int left, int mid, int right) {

		for (int i = left; i <= right; i++) {
			temp_tab[i] = tab[i];  //pomocnicza tablica do operowania na oryginalnych wartosciach tablicy i wstawiania ich w dobre miejsca
		}
		int pointer1 = left;   //pierwszy element pierwszej tablicy
		int pointer2 = mid + 1;  //pierwszy element drugiej tablicy
		int pointer0 = left;   //miejsce na najmniejszy element tablicy wynikowej

		while (pointer1 <= mid && pointer2 <= right) {   //laczenie az sie nie skoncza elementy z dwoch tablic i wpisywanie do wynikowej
			if (temp_tab[pointer1] <= temp_tab[pointer2]) {
				tab[pointer0] = temp_tab[pointer1];
				pointer1++;
			}                      //wpisanie do tablicy wynikowej elementu mniejszego po porownaniu i przesuniecie tam granicy
			else {
				tab[pointer0] = temp_tab[pointer2];
				pointer2++;
			}
			pointer0++;
		}
		while (pointer1 <= mid) {  //gdy skoncza nam sie elementy w drugiej tablicy i zostana nam elementy tylko pierwszej
			tab[pointer0] = temp_tab[pointer1];
			pointer0++;
			pointer1++;
		}

	}
	void mergeSort(T *tab, int left, int right) {
		if (left < right) {
			int mid = (left + right) / 2;   //dzielenie tablicy na pol
			mergeSort(tab, left, mid);      //rekurencyjne dzielenie az do tablicy jednoelementowej
			mergeSort(tab, mid + 1, right);
			merge(tab, left, mid, right);  //polaczenie 
		}
	}
public:
	void sort(T *tab_to_sort, long int rozmiar) {
		temp_tab = new T[rozmiar];
		mergeSort(tab_to_sort, 0, rozmiar - 1);
		delete[]temp_tab;
	}
};

template <typename T>
class HeapSort {
private:
	void maxKopiec(T *tab, int rozmiar_kopca, int korzen) {  //stworzenie maksymalnego kopca
		int max_index = korzen;          //najwieksza wartosc sposrod korzenia i jego dwojki drzew (poczatkowo korzen)
		int l_drzewo = korzen * 2 + 1;  //index lewego drzewa od korzenia
		int r_drzewo = korzen * 2 + 2;  //index prawefo drzewa od korzenia

		if (l_drzewo < rozmiar_kopca && tab[l_drzewo] > tab[max_index]) {
			max_index = l_drzewo;
		}                                    //ustalenie maksymalnej wartosci sposrod korzenia i dwojki drzew
		if (r_drzewo < rozmiar_kopca && tab[r_drzewo] > tab[max_index]) {
			max_index = r_drzewo;
		}
		if (max_index != korzen) {
			swap(tab, max_index, korzen);   //jesli maksymalna wartosc zmienila swoja wartosc to zamiana
			maxKopiec(tab, rozmiar_kopca, max_index);  //rekrencyjne wywolanie funkcji
		}
	}
public:
	void sort(T *tab_to_sort, long int rozmiar) {
		int n = rozmiar;
		for (int i = n / 2 - 1; i >= 0; i--) {   //ostatni korzen;az do najstarszego korzenia;poruszamy sie w gore kopca wiec zmniejszamy licznik
			maxKopiec(tab_to_sort, n, i);      //poruszamy sie w gore po kopcu tworzac go maksymalnym (korzen wiekszy od jego drzew)
		}
		for (int i = n - 1; i > 0; i--) { //poruszamy sie w gore po kopcu zamieniajac pierwszy element z ostatnim
			swap(tab_to_sort, 0, i);
			n--;
			maxKopiec(tab_to_sort, n, 0); //po zamianie elementow, umiejscowieniu najwiekszego elementu, zmniejszeniu rozmiaru tworzymy znow maksymalny kopiec
		}
	}
};

template <typename T>
class ShellSort {
private:
	
	void shellSort(T *tab, long int rozmiar)
	{
		for (int odleglosc = rozmiar / 2; odleglosc > 0; odleglosc /= 2)  //ustawienie poczatkowej odleglosci dwoch sasiednich elementow, z kazdym przejsciem dzielenie na 2 az do 1
		{
			
			for (int i = odleglosc; i < rozmiar; i++) //poruszanie sie po tablicy
			{
				int temp = tab[i];

				int j;
				for (j = i; j >= odleglosc && tab[j - odleglosc] > temp; j -= odleglosc)
					tab[j] = tab[j - odleglosc];  //zamiana jesli jest konieczna

				tab[j] = temp;
			}
		}
	}
public:
	void sort(T *tab_to_sort, long int rozmiar) {
		int n = rozmiar;
		shellSort(tab_to_sort, n);
	}
};


template <typename T>
class Testowanie {
private:
	long int rozmiar[5] = { 10000, 50000, 100000, 500000, 1000000 };
	double procent[7] = { 0, 25, 50, 75, 95, 99, 99.7 };
	double liczba_tablic = 100;
	double suma = 0;
	double srednia = 0;
	MergeSort<T> m;
	QuickSort<T> q;
	HeapSort<T> h;
	ShellSort<T> s;
	clock_t start, stop;
	int zakres = 10000000;
	double czas = 0;
	double min_czas;
	double max_czas;
public:
	void testowanie(int metoda_sortowania) {
		fstream wyniki("Wyniki.txt", ios::app);
		for (int j = 0; j < 5; j++) {
			for (int i = 0; i < 7; i++) {
				min_czas = 9999;
				max_czas = 0;
				for (int k = 1; k <= liczba_tablic; k++) {
					T *tab;
					tab = new T[rozmiar[j]];
					losuj_tab(tab, rozmiar[j], zakres, procent[i]);
					
					switch (metoda_sortowania) {
					case 0:
					{
						start = clock();
						h.sort(tab, rozmiar[j]);
						stop = clock();
					}	
						break;
					case 1:
					{
						start = clock();
						q.sort(tab, rozmiar[j]);
						stop = clock();
					}	
						break;
					case 2:
					{
						start = clock();
						m.sort(tab, rozmiar[j]);
						stop = clock();
					}
						break;
					case 3:
					{
						start = clock();
						s.sort(tab, rozmiar[j]);
						stop = clock();
					}
						break;
					default:
						break;
					}
					czas = (stop - start) / (double)CLOCKS_PER_SEC;
					suma += czas;
					if (min_czas > czas) {
						min_czas = czas;
					}
					if (max_czas < czas) {
						max_czas = czas;
					}
					if (k == liczba_tablic) {

						if (k == 1) {
							wyniki << "minimum: " << procent[i] << "  " << rozmiar[j] << "  " << czas << " sekund" << endl;				
							wyniki << "maximum: " << procent[i] << "  " << rozmiar[j] << "  " << czas << " sekund" << endl;

						}

						else {
							wyniki << "minimum: " << procent[i] << "  " << rozmiar[j] << "  " << min_czas << " sekund" << endl;
							wyniki << "maximum: " << procent[i] << "  " << rozmiar[j] << "  " << max_czas << " sekund" << endl;
						}
					}
					delete[]tab;
				}
				srednia = suma / liczba_tablic;
				wyniki << "srednia: " << procent[i] << "  " << rozmiar[j] << "  " << srednia << " sekund" << endl;
				suma = 0;
			}

			min_czas = 9999;
			max_czas = 0;

			for (int k = 1; k <= liczba_tablic; k++) {
				
				T *tab2;
				tab2 = new T[rozmiar[j]];
				losuj_tab(tab2, rozmiar[j], zakres, 100);
				odwroc_tab(tab2, rozmiar[j]);

				switch (metoda_sortowania) {
				case 0:
				{
					start = clock();
					h.sort(tab2, rozmiar[j]);
					stop = clock();
				}
					break;
				case 1:
				{
					start = clock();
					q.sort(tab2, rozmiar[j]);
					stop = clock();
				}
					break;
				case 2:
				{
					start = clock();
					m.sort(tab2, rozmiar[j]);
					stop = clock();
				}
					break;
				case 3:
				{
					start = clock();
					s.sort(tab2, rozmiar[j]);
					stop = clock();
				}
					break;
				default:
					break;
				}
				czas = (stop - start) / (double)CLOCKS_PER_SEC;
				suma += czas;
				if (min_czas > czas) {
					min_czas = czas;
				}
				if (max_czas < czas) {
					max_czas = czas;
				}
				if (k == liczba_tablic) {

					if (k == 1) {
						wyniki << "minimum: " << "odwrocone" << "  " << rozmiar[j] << "  " << czas << " sekund" << endl;
						wyniki << "maximum: " << "odwrocone" << "  " << rozmiar[j] << "  " << czas << " sekund" << endl;

					}

					else {
						wyniki << "minimum: " << "odwrocone" << "  " << rozmiar[j] << "  " << min_czas << " sekund" << endl;
						wyniki << "maximum: " << "odwrocone" << "  " << rozmiar[j] << "  " << max_czas << " sekund" << endl;
					}
				}
				delete[]tab2;
			}
			srednia = suma / liczba_tablic;
			wyniki << "srednia: " << "odwrocone" << "  " << rozmiar[j] << "  " << srednia << " sekund" << endl;
			suma = 0;

		}

	}
};

int main() {
	srand(time(NULL)); //zapobiegniecie takiego samego losu za kazdym odpaleniem
	cout.setf(ios::fixed); //notacja zwykla, czyli nie wywali wyniku typu 1.175000e+003	

	Testowanie<int> tescik;
	remove("Wyniki.txt");
	
	fstream wyniki;
	wyniki.open("Wyniki.txt", ios::app);
	
	wyniki << " HeapSort " << endl << endl;
	tescik.testowanie(0);
	//wyniki << endl << endl << " Quicksort " << endl << endl;
	//tescik.testowanie(1);
	wyniki << endl << endl << " MergeSort " << endl << endl;
	tescik.testowanie(2);
	wyniki << endl << endl << " ShellSort " << endl << endl;
	tescik.testowanie(3);

	wyniki.close();
}




