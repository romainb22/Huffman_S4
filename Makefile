CFLAGS = -W -Wall -pedantic -O3 `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`


main : clean noeud.o tableau.o compression.o decompression.o
	gcc $(CFLAGS) $(LDFLAGS) main.c noeud.o tableau.o compression.o decompression.o $(LDLIBS) -o main

noeud.o :
	gcc $(CFLAGS) -c noeud.c -o noeud.o

tableau.o :
	gcc $(CFLAGS) -c tableau.c -o tableau.o

compression.o :
	gcc $(CFLAGS) -c compression.c -o compression.o

decompression.o :
	gcc $(CFLAGS) -c decompression.c -o decompression.o

clean :
	rm -rf *.o main

