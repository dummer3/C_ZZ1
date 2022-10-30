/* ----------------------------------------- */
/* nom du fichier : doc.h                    */
/* rôle : créer une doc en récupérant les    */
/*        commentaires et autres             */
/* ----------------------------------------- */

#ifndef MAIN_H
#define MAIN_H

// structure pour définir une cellule
typedef struct cellule {
  char *ligne;
  struct cellule *suiv;
} cellule_t;

// structure pour définir une liste
typedef struct liste {
  cellule_t *tete;
  cellule_t *fin;
} liste_t;

/* -------------------------------------------------------------------- */
/* insertEnd         Insère une cellule en fin de liste                 */
/*                                                                      */
/* En entrée: une liste_t et une cellule_t                              */
/*                                                                      */
/* En sortie: rien                                                      */
/* -------------------------------------------------------------------- */
void insertEnd(liste_t *l, cellule_t *c);

/*commentaire
 * de plusieurs
 * lignes
 */

/*commentaire
 * de plusieurs
 lignes */

void addStart(liste_t *l, cellule_t *c);
cellule_t *newCellule(char *s);
liste_t *newListe();
void affich(liste_t *l);
void freeListe(liste_t *l);

#endif
