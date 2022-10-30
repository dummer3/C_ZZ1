#ifndef MAIN_H
#define MAIN_H

typedef struct cellule {
  char *ligne;
  struct cellule *suiv;
} cellule_t;

typedef struct liste {
  cellule_t *tete;
  cellule_t *fin;
} liste_t;

#endif

void insertEnd(liste_t *l, cellule_t *c);
void addStart(liste_t *l, cellule_t *c);
cellule_t *newCellule(char *s);
liste_t *newListe();
void affich(liste_t *l);
