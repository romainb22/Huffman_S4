CFLAGS = -W -Wall -pedantic -O3

main : noeud.o tableau.o
	gcc $(CFLAGS) main.c noeud.o tableau.o -o main

noeud.o :
	gcc $(CFLAGS) -c noeud.c -o noeud.o

tableau.o :
	gcc $(CFLAGS) -c tableau.c -o tableau.o

clean :
	rm -rf */*.o *.o main

