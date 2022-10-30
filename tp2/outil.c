#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void saisir(char * s) 
{
  printf("Saisir une chaine\n");
  scanf("%s", s);
}

int main() 
{
  char *s[255] ;

  printf("Entrer votre prenom. ");
  saisir(s);
  printf("Bonjour %s!\n", s);

  if (strcmp(s,"ddd")) printf("bizarre \n");

  return 0;
}
