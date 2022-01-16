all: Q1a Q1b Q2

Q1a: q1a.c
	gcc -E q1a.c -o q1a.i
	gcc -S q1a.c
	gcc -c q1a.c
	gcc q1a.c -o q1a

Q1b: q1b.c
	gcc -E q1b.c -o q1b.i
	gcc -S q1b.c
	gcc -c q1b.c
	gcc q1b.c -pthread -o q1b

Q2: q2.c
	nasm -f elf64 -o B.o B.asm
	gcc -E q2.c -o q2.i
	gcc -S q2.c
	gcc -c q2.c
	gcc -no-pie q2.c B.o -o q2

clean:
	rm *.o *.s *.i q1a q1b q2

run:
	./q1a student_record.csv
	./q1b student_record.csv
	./q2
