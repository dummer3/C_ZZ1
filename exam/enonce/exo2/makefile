exo2:exo2.o code.o  ../teZZt.o
	gcc -o exo2 exo2.o code.o ../teZZt.o -lm 
	@echo "Lancer le programme avec  ./exo2" 
../teZZt.o:../teZZt.h ../teZZt.c
	gcc -c ../teZZt.c -o ../teZZt.o
exo2.o:exo2.c code.h 
	gcc -c exo2.c -g -Wall -Wextra
code.o:code.h code.c
	gcc -c code.c -g -Wall -Wextra 
clean:
	rm -rf exo1 code.o examen.o *.gch
