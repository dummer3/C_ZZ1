#ifndef FLOOD_H
#define FLOOD_H

#define COULEURS 6
#define TAILLE 12

typedef struct {
  int r;
  int g;
  int b;
} couleur_t;

couleur_t *aleaCouleur();
void initialiser(int tab[][TAILLE]);
void afficherGrille(int tab[][TAILLE]);
void afficherGrilleCouleur(int tab[][TAILLE]);
int fin(int tab[][TAILLE]);
void remplir(int tab[][TAILLE], int couleur_prec, int couleur_actu, int i,
             int j);
#endif
