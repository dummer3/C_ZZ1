/**
 * Ce programme sert de base pour tester le profilage de programme.
 * Il faut compiler ce proogramme avec l'option -pg, l'executer (ce qui genere un rapport de performance).
 * La derniere etape est l'analyse avec gprof executable.
 *
 * \author loic & bruno
 * \date 24 janvier 2011
 */
#include <stdio.h>
#include <stdlib.h>

#define TAILLE 10000000
#define MAXX(A,B) ((A)>(B))?(A):(B)

/**
 * Fonction qui calcule le maximum de deux reels
 * \param a premier parametre
 * \param b deuxieme parametre
 * \return le plus grand des deux nombres a ou b
 */
double maxx(double a, double b)
{
   return (a>b)?a:b;
}

/** 
 * Fonction qui manipule un tableau de reel avec une macro
 * \param t le tableau a manipuler
 */
void essai_macro(double * t)
{
   int i;

   for(i=1; i<TAILLE; ++i)
    t[i] = MAXX(t[i-1], t[i]);
}

/** 
 * Fonction qui manipule un tableau de reel avec une fonction
 * \param t le tableau a manipuler
 */
void essai_fonction(double * t)
{
   int i;
   
   for(i=1; i<TAILLE; ++i)
      t[i] = maxx(t[i-1], t[i]);
}

/**
 * Fonction principale du programme. 
 * Permet de comparer l'utilisation de macro ou de fonction pour le meme traitement
 */
int main()
{
   double * tab1 = (double *)malloc(TAILLE*sizeof(double));
   double * tab2 = (double *)malloc(TAILLE*sizeof(double));

   int i; /* erreur par valgrind */

   for (i=0; i< TAILLE; ++i)
      tab2[i] = tab1[i] = rand()/(RAND_MAX+1.0);

   for (i=0; i<10; ++i) essai_macro(tab2);

   for (i=0; i< TAILLE; ++i)
      tab2[i] = tab1[i];

   for (i=0; i<10; ++i) essai_fonction(tab2);

   /* free(tab1); */ /* pour valgrind */
   free(tab2);
   
   return 0;
}
