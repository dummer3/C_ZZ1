#include "doc.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  char s[256];
  char *result;
  liste_t *l = newListe();
  regex_t regexPrototype;
  regex_t regexCommentaire;
  printf("\n|| Début regex ||\n");

  if (regcomp(&regexPrototype,
              "^(\\S[^\\-\\+\\*\\=\\|&])+\\s+(\\S[^\\-\\+\\*=&\\|])+.*(\\);|\\)"
              "|\\)\\s*\\{).{0,1}$",
              REG_EXTENDED)) {
    printf("ERREUR LORS DE LA CREATION DU REGEX PROTOTYPE");
    exit(-1);
  }
  if (regcomp(&regexCommentaire, "(//|/\\*|\\*/|^\\s*\\*)", REG_EXTENDED)) {
    printf("ERREUR LORS DE LA CREATION DU REGEX COMMENTAIRE");
    exit(-1);
  }

  printf("|| regex crée||\n");

  if (argc <= 1) {
    printf("AUCUN FICHIER DONNER EN ARGUMENT\n");
    exit(-1);
  }

  if (argv[1][strlen(argv[1]) - 1] != 'c' &&
      argv[1][strlen(argv[1]) - 1] != 'h') {
    printf("LE FICHIER FOURNI N'EST PAS UN FICHIER SOURCE C (OU EN-TETE H)\n");
    exit(-1);
  }

  FILE *F = fopen(argv[1], "r");
  FILE *W = fopen("doc.txt", "w");
  if (F == NULL || W == NULL) {
    printf("UN DES FICHIERS N'AS PAS PU ETRE OUVERT\n");
    exit(-1);
  }
  printf("|| Fichier crée ||\n");

  do {
    result = fgets(s, 256, F);
    if (result != NULL &&
        (s[0] == '#' || !regexec(&regexPrototype, s, 0, NULL, 0) ||
         !regexec(&regexCommentaire, s, 0, NULL, 0))) {
      if (s[strlen(s) - 2] == '{') {
        s[strlen(s) - 2] = ';';
      }
      insertEnd(l, newCellule(s));
      fwrite(s, 1, strlen(s), W);
    }
  } while (result != NULL);
  fclose(F);
  fclose(W);
  affich(l);
  regfree(&regexPrototype);
  regfree(&regexCommentaire);
  freeListe(l);
  return 0;
}
