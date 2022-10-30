#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define NB 3

void fermetureAlea(int * tab[])
{
	srand(time(0));
	int alea = rand()%NB;

	for(int i = 0; i < NB;i++)
	{
		*tab[i] = 0;
	}
	*tab[alea] = 1;
}

void affichage(int * tab[])
{
	for(int i = 0; i < NB;i++)
	{
		printf("%d\n",*tab[i]);
	}

}

int main()
{
	int guichet_A,guichet_B,guichet_C;
	int * tab[100];
	tab[0] = &guichet_A;
	tab[1] = &guichet_B;
	tab[2] = &guichet_C;
	fermetureAlea(tab);
	affichage(tab);
}
