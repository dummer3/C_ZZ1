#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s {
  char nom[100];
  char langage[100];
  int annee;
} s_t;

s_t init(char *s, char *n, int i) {
  s_t l;
  strcpy(l.nom, s);
  strcpy(l.langage, n);
  l.annee = i;
  return l;
}

int main() {
  s_t tab[] = {init("Backus John", "FORTRAN", 1957),
               init("Goldfarb Charles", "GML", 196),
               init("Wirth Niklaus", "Pascal", 1970),
               init("Ritchie Dennis", "C", 1972),
               init("Kernighan Brian", "C", 1972),
               init("Sussman Gerald Jay", "Scheme", 1975),
               init("Steele Guy L", "Scheme", 1975),
               init("Naughton Patrick", "Java", 1983),
               init("Cox Brad", "Objective C", 1983),
               init("Berners Lee Tim", "WWW", 1990)};
  return 0;
}
