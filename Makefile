CFLAGS = -W -Wall -pedantic -O3 `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`

all : v0 v1

versions :
	@echo "v0 v1"

v0 : clean noeud.o tableau.o compression.o decompression.o
	@gcc $(CFLAGS) $(LDFLAGS) huffman_v0.c noeud.o tableau.o compression.o decompression.o $(LDLIBS) -o v0
	@echo "Compilation de la v0"

v1 : clean noeud.o tableau.o compression.o decompression.o
	@gcc $(CFLAGS) $(LDFLAGS) huffman_v1.c noeud.o tableau.o compression.o decompression.o $(LDLIBS) -o v1
	@echo "Compilation de la v1"

noeud.o :
	@gcc $(CFLAGS) -c noeud.c -o noeud.o

tableau.o :
	@gcc $(CFLAGS) -c tableau.c -o tableau.o

compression.o :
	@gcc $(CFLAGS) -c compression.c -o compression.o

decompression.o :
	@gcc $(CFLAGS) -c decompression.c -o decompression.o

ref :
	@doxygen config

clean :
	@rm -rf *.o v* *~ html latex

cleanb : 
	@rm -rf *.bc
