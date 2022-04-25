CFLAGS = -W -Wall -pedantic -O3

main :
	gcc $(CFLAGS) main.c noeud.h -o main

clean :
	rm -rf */*.o main

