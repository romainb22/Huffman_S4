CFLAGS = -W -Wall -pedantic -O3 `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`


main : clean noeud.o tableau.o
	gcc $(CFLAGS) $(LDFLAGS) main.c noeud.o tableau.o $(LDLIBS) -o main

noeud.o :
	gcc $(CFLAGS) -c noeud.c -o noeud.o

tableau.o :
	gcc $(CFLAGS) -c tableau.c -o tableau.o

clean :
	rm -rf */*.o *.o main

