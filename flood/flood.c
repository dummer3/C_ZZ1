#include "flood.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

couleur_t *aleaCouleur() {
  printf("coucou\n");
  srand(time(0));
  couleur_t *couleurs = malloc(sizeof(couleur_t) * COULEURS);
  for (int i = 0; i < COULEURS; i++) {
    couleurs[i].r = rand() % 125 + 75;
    couleurs[i].g = rand() % 125 + 75;
    couleurs[i].b = rand() % 125 + 75;
  }
  return couleurs;
}

void initialiser(int tab[][TAILLE]) {
  srand(time(0));
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      tab[i][j] = rand() % COULEURS;
    }
  }
}

void afficherGrille(int tab[][TAILLE]) {
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      printf("|%d", tab[i][j]);
    }
    printf("|\n");
  }
}

void afficherGrilleCouleur(int tab[][TAILLE]) {
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      printf("\033[%d;10m %d \033[0m", tab[i][j] + 41, tab[i][j]);
    }
    printf("|\n");
  }
}

int fin(int tab[][TAILLE]) {
  int verif = tab[0][0];
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      if (verif != tab[i][j]) {
        return 0;
      }
    }
  }
  return 1;
}

void remplir(int tab[][TAILLE], int couleur_prec, int couleur_actu, int i,
             int j) {

  tab[i][j] = couleur_actu;
  if (i - 1 >= 0 && tab[i - 1][j] == couleur_prec) {
    remplir(tab, couleur_prec, couleur_actu, i - 1, j);
  }
  if (i + 1 < TAILLE && tab[i + 1][j] == couleur_prec) {
    remplir(tab, couleur_prec, couleur_actu, i + 1, j);
  }
  if (j - 1 >= 0 && tab[i][j - 1] == couleur_prec) {
    remplir(tab, couleur_prec, couleur_actu, i, j - 1);
  }
  if (j + 1 < TAILLE && tab[i][j + 1] == couleur_prec) {
    remplir(tab, couleur_prec, couleur_actu, i, j + 1);
  }
}
