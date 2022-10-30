#include<stdio.h>
#include<stdlib.h>

int main()
{
	FILE * fichier;

	fichier = fopen("nom_du_fichier", "r");
	if (fichier) {
		printf("on peut lire le fichier\n");
		// utilisation
		// fclose(fichier);
	} else printf("on ne peut pas l'utiliser\n");

}
