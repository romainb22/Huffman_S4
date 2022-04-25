CFLAGS = -W -Wall -pedantic -O3

main : noeud.o
	gcc $(CFLAGS) main.c noeud.o -o main

noeud.o :
	gcc $(CFLAGS) -c noeud.c -o noeud.o

clean :
	rm -rf */*.o *.o main

