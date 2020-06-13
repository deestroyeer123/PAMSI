CC = g++ -std=c++11

all: main.o kruskal.o testowanie.o M_Graf.o L_Graf.o Lista.o prim.o
	$(CC) main.o kruskal.o testowanie.o M_Graf.o L_Graf.o Lista.o prim.o -o a.out
	./a.out

main.o: main.cpp kruskal.h testowanie.h prim.h L_Graf.h
	$(CC) main.cpp -c -o main.o

kruskal.o: kruskal.cpp kruskal.h M_Graf.o L_Graf.h
	$(CC) kruskal.cpp -c -o kruskal.o

M_Graf.o: M_Graf.cpp M_Graf.h
	$(CC) M_Graf.cpp -c -o M_Graf.o

L_Graf.o: L_Graf.cpp L_Graf.h Lista.h
	$(CC) L_Graf.cpp -c -o L_Graf.o

Lista.o: Lista.cpp Lista.h
	$(CC) Lista.cpp -c -o Lista.o

prim.o: prim.cpp prim.h M_Graf.h L_Graf.h
	$(CC) prim.cpp -c -o prim.o

testowanie.o: testowanie.cpp testowanie.h M_Graf.h
	$(CC) testowanie.cpp -c -o testowanie.o

clean:
	rm -r *.o