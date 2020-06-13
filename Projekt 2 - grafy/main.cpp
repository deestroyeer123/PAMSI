#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include "M_Graf.h"
#include "kruskal.h"
#include "prim.h"
#include "testowanie.h"
#include "L_Graf.h"
using namespace std;




int main()
{
	
	srand(time(NULL)); //zapobiegniecie takiego samego losu za kazdym odpaleniem
	remove("Wyniki_macierz.txt");
	remove("Wyniki_lista.txt");
	Test tescik;

	fstream wyniki, wyniki2;
	
	wyniki.open("Wyniki_macierz.txt", ios::app);
	wyniki << "kruskal macierz" << endl;
	tescik.test(0,0);
	wyniki << "prima macierz" << endl;
	tescik.test(0,1);
	wyniki.close();
	
	wyniki2.open("Wyniki_lista.txt", ios::app);
	wyniki2 << "kruskal lista" << endl;
	tescik.test(0,0);
	wyniki2 << "prima lista" << endl;
	tescik.test(0,1);
	wyniki2.close();

}
