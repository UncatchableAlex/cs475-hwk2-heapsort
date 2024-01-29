all: main.c heap.h employee.h heap.o
	gcc -Wall -g -o heapsort main.c heap.o
	gcc -Wall -g -o testcase testcase.c

heap.o: heap.h heap.c
	gcc -Wall -g -c heap.c
clean:
	rm -f heapsort *.o
