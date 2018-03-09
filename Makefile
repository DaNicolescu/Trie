build: tema3.o Functions.o
	gcc -g tema3.o Functions.o -o tema3
tema2.o: tema3.c
	gcc -c tema3.c
Functions.o: Functions.c
	gcc -c Functions.c
clean:
	rm -f *.o tema3
