exo1:exo1.o code.o  ../teZZt.o
	gcc -o exo1 exo1.o code.o ../teZZt.o -lm 
	@echo "Lancer le programme avec  ./exo1" 
../teZZt.o:../teZZt.h ../teZZt.c
	gcc -c ../teZZt.c -o ../teZZt.o
exo1.o:exo1.c code.h 
	gcc -c exo1.c -g -Wall -Wextra
code.o:code.h code.c
	gcc -c code.c -g -Wall -Wextra 
clean:
	rm -rf exo1 code.o examen.o *.gch
