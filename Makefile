CFLAGS = -W -Wall -pedantic -O3

q4_1 :
	gcc $(CFLAGS) question4_1.c -o main

clean :
	rm -rf */*.o main

