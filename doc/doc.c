/*
 * \file      doc.c
 * \brief     Create doc.
 * \details   This class is used to demonstrate a number of section commands.
 * \author    John Doe
 * \version   4.1a
 * \date      1990-2011
 * \pre       First initialize the system.
 * \bug       Not all memory is freed when deleting an object of this class.
 * \warning   Improper use can crash your application
 * \copyright GNU Public License.
 */

#include "doc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void affich(liste_t *l) {
  printf(""
         "\n|---------------------------------------------------------------|\n"
         "|                           AFFICHAGE                           |\n"
         "|---------------------------------------------------------------|\n\n"
         "");
  if (l != NULL) {
    cellule_t *c = l->tete;
    while (c != NULL) {
      printf("%s", c->ligne);
      c = c->suiv;
    }
  }
  printf(""
         "\n|---------------------------------------------------------------|\n"
         "|                         FIN AFFICHAGE                         |\n"
         "|---------------------------------------------------------------|\n\n"
         "");
}

void insertEnd(liste_t *l, cellule_t *c) {
  if (l->tete == NULL) {
    l->tete = c;
  } else {
    l->fin->suiv = c;
  }
  l->fin = c;
}
void addStart(liste_t *l, cellule_t *c) {
  if (l->tete == NULL) {
    l->fin = c;
  } else {
    c->suiv = l->tete;
  }
  l->tete = c;
}

liste_t *newListe() {
  liste_t *l = malloc(sizeof(liste_t));
  l->tete = NULL;
  l->fin = NULL;
  return l;
}

void freeListe(liste_t *l) {
  cellule_t *c = l->tete;
  while (c != NULL) {
    l->tete = c->suiv;
    free(c->ligne);
    free(c);
    c = l->tete;
  }
  free(l);
}
cellule_t *newCellule(char *s) {
  cellule_t *c = malloc(sizeof(cellule_t));
  c->suiv = NULL;
  c->ligne = malloc(strlen(s) + 1);
  strcpy(c->ligne, s);
  return c;
}
