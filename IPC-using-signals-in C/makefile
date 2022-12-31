all: Main SR ST Test

Main: main.c
	gcc -E main.c -o main.i
	gcc -S main.c
	gcc -c main.c
	gcc main.c -o main

SR: SR.c
	gcc -E SR.c -o SR.i
	gcc -S SR.c
	gcc -c SR.c
	gcc SR.c -o SR

ST: ST.c
	gcc -E ST.c -o ST.i
	gcc -S ST.c
	gcc -c ST.c
	gcc ST.c -o ST

Test: test.c
	gcc -E test.c -o test.i
	gcc -S test.c
	gcc -c test.c
	gcc test.c -o test

clean:
	rm *.o *.s *.i main ST SR test

run:
	./test
	./main
	