code1: sales-project.c
	gcc sales-project.c -o code1

code2: matrix-lab.c
	gcc matrix-lab.c -o code2

clean:
	rm -f *.o code1 code2
