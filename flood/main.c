#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define COULEURS 6
#define TAILLE 12

void initialiser(int tab[][12])
{
	srand(time(0));
	for(int i = 0; i < TAILLE; i++)
	{
		for(int j = 0; j < TAILLE; j++)
		{
			tab[i][j] = rand()%COULEURS;
		}
	}
}

void afficherGrille(int tab[][12])
{
	for(int i = 0; i < TAILLE; i++)
	{
		for(int j = 0; j < TAILLE; j++)
		{
			printf("|%d",tab[i][j]);
		}
		printf("|\n");
	}
}

void afficherGrilleCouleur(int tab[][12])
{
	for(int i = 0; i < TAILLE; i++)
	{
		for(int j = 0; j < TAILLE; j++)
		{
			printf("\033[%d;10m %d \033[0m",tab[i][j]+41,tab[i][j]);
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

void remplir(int tab[][12], int couleur_prec, int couleur_actu, int i, int j) {
  printf("%d %d\n", i, j);
  if (tab[i][j] == couleur_prec) {
    tab[i][j] = couleur_actu;
    if (i - 1 >= 0) {
      remplir(tab, couleur_prec, couleur_actu, i - 1, j);
    }
    if (i + 1 < TAILLE) {
      remplir(tab, couleur_prec, couleur_actu, i + 1, j);
    }
    if (j - 1 >= 0) {
      remplir(tab, couleur_prec, couleur_actu, i, j - 1);
    }
    if (j + 1 < TAILLE) {
      remplir(tab, couleur_prec, couleur_actu, i, j + 1);
    }
  }
}

int main()
{
	int tab[TAILLE][TAILLE];
	int round = 0;
	initialiser(tab);
	afficherGrilleCouleur(tab);
	int choix = -1;
	do
	{
		printf("entrer une couleur\n");
		scanf("%d",&choix);
		if(choix == -1)
		{
			printf("fin du jeux\n");
		}
		else if (choix < 0 && choix >= COULEURS)
		{
			printf("couleur non comprise dans le tableau\n");
		}
		else if(choix != tab[0][0])
		{
			round++;
			remplir(tab,tab[0][0],choix,0,0);
		}
		afficherGrilleCouleur(tab);
	}
	while(!fin(tab) && round <22 && choix != -1);
}
