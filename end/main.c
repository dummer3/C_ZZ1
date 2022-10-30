#include <dirent.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void affDir(char *s) {
  struct dirent *lecture;
  DIR *rep;
  rep = opendir(s);
  while ((lecture = readdir(rep))) {
    printf("%s\n", lecture->d_name);
  }
  closedir(rep);
}
void fonc(int nbr, ...) {
  va_list l;
  va_start(l, nbr);
  while (nbr--) {
    affDir(va_arg(l, char *));
    printf("\n--------------------------------------------------------\n");
  }
  va_end(l);
}

void fonc2(char *s, ...) {
  va_list l;
  va_start(l, -1);
  do {
    affDir(s);
    printf("\n--------------------------------------------------------\n");
    s = va_arg(l, char *);
  } while (s != NULL);
  va_end(l);
}

int main() {
  fonc(2, "../", "../../");
  fonc2("../", "../../", "../", "../../", NULL);
}
