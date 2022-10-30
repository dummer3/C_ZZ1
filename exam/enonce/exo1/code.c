#include "code.h"

#include <stdlib.h>

char *init(char *tab, int taille) {
  if (!tab)
    tab = malloc(sizeof(int) * taille);
  for (int i = 2; i < taille; i++) {
    tab[i] = 1;
  }
  tab[0] = tab[1] = 0;
  return tab;
}

void affichage(FILE *file, char *tab, int taille) {
  int first = 1;
  for (int i = 0; i < taille; i++) {
    if (tab[i]) {
      if (first) {
        fprintf(file, "%d", i);
        first--;
      } else {
        fprintf(file, " %d", i);
      }
    }
  }
}

void suppMultiple(char *tab, int taille, int nb) {
  for (int i = nb * 2; i < taille; i += nb) {
    tab[i] = 0;
  }
}

int prochainNombre(char *tab, int taille, int nb) {
  int i = ++nb;
  while (i < taille && !tab[i])
    i++;
  return i >= taille ? -1 : i;
}

int listeNombrePremiers(FILE *file, int taille) {
  if (!file) {
    printf("ERROR WHEN OPEN FILE\n");
    return -1;
  }
  int i = 2, count = 0;
  char *tab = NULL;
  tab = init(tab, taille);
  while (i != -1) {
    printf("%d\n", i);
    suppMultiple(tab, taille, i);
    i = prochainNombre(tab, taille, i);

    count++;
  }
  affichage(file, tab, taille);
  free(tab);
  return count;
}
