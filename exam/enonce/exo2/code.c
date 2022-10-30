#include "code.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// ********************************************************
//  TESTS DES FONCTIONS POUR FICHIERS STATIQUES
// ********************************************************

void static_insert(char fichier[LINES][COLUMNS], int i) {
  
}

void static_export(FILE *file, char fichier[LINES][COLUMNS]) {
  int i = 0;
  if (file) {
    while (i < LINES && fichier[i][0] != EOF) {
      fputs(fichier[i++], file);
    }
  }
}

void static_import_text(char *nom, char fichier[LINES][COLUMNS]) {
  FILE *f = fopen(nom, "r");
  int i = 0;
  if (f) {
    while (fgets(fichier[i], COLUMNS, f)) {
      i++;
    }
  }
  fichier[i][0] = EOF;
}

// ********************************************************
//  TESTS DES FONCTIONS POUR FICHIERS DYNAMIQUES
// ********************************************************

text *dynamic_import_text(char *nom) {
  FILE *f = fopen(nom, "r");
  text *list = NULL;
  char buffer[COLUMNS];
  if (f) {
    list = malloc(sizeof(text));
    text *act = list;
    while (fgets(buffer, COLUMNS, f)) {
      strcpy(act->content, buffer);
      act->next = malloc(sizeof(text));
      act = act->next;
    }
    act->content[0] = EOF;
    act->next = NULL;
  }
  return list;
}

void dynamic_export(FILE *file, text *t) {
  if (file) {
    while (t != NULL && t->content[0] != EOF) {
      fputs(t->content, file);
      t = t->next;
    }
  }
}

void dynamic_insert(text **t, int i) {}

void dynamic_add(text **t, char *chaine) {
  if (*t) {
    text *tmp = *t;
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = malloc(sizeof(text));
    strcpy(tmp->next->content, chaine);
    tmp->next->next = NULL;
  } else {
    *t = malloc(sizeof(text));
    strcpy((*t)->content, chaine);
    (*t)->next = NULL;
  }
}

void dynamic_free(text **t) {
  text *tempo;
  if (!t) {
    while ((*t)->next) {
      tempo = (*t)->next->next;
      free(tempo);
    }
  }
  free(*t);
}

// ********************************************************
//  TESTS DES FONCTIONS UTILITAIRES
// ********************************************************

void decalGauche(char *ligne, int pos) {
  int i = pos;
  while (i <= (int)strlen(ligne)) {
    ligne[i - pos] = ligne[i];
    i++;
  }
}

int is_header(char *ligne) {
  int i = 0;
  while (ligne[i] == '#') {
    i++;
  }
  decalGauche(ligne, i);
  return i;
}

void decalDroite(char *ligne, int pos, int length) {
  int i = strlen(ligne);
  while (i > pos) {
    ligne[i + length] = ligne[i];
    i--;
  }
}

void emphasis(char *ligne) {
  int posEt, posBa;
  posEt = posBa = -1;

  for (int i = 0; i < (int)strlen(ligne); i++) {
    if (ligne[i] == '*') {
      if (posEt != -1) {
        decalDroite(ligne, i, 3);
        ligne[i] = '<';
        ligne[i + 1] = '/';
        ligne[i + 2] = 'i';
        ligne[i + 3] = '>';
        decalDroite(ligne, posEt, 2);

        ligne[posEt] = '<';
        ligne[posEt + 1] = 'i';
        ligne[posEt + 2] = '>';
        posEt = -1;
      } else {
        posEt = i;
      }
    } else if (ligne[i] == '_') {
      if (posBa != -1) {
        decalDroite(ligne, i, 3);
        ligne[i] = '<';
        ligne[i + 1] = '/';
        ligne[i + 2] = 'i';
        ligne[i + 3] = '>';
        decalDroite(ligne, posBa, 2);
        ligne[posBa] = '<';
        ligne[posBa + 1] = 'i';
        ligne[posBa + 2] = '>';
        posBa = -1;
      } else {
        posBa = i;
      }
    }
  }
}

void strong_emphasis(char *ligne) {
  int posEt, posBa;
  posEt = posBa = -1;

  for (int i = 0; i < (int)strlen(ligne) - 1; i++) {
    if (ligne[i] == '*' && ligne[i + 1] == '*') {
      if (posEt != -1) {
        decalDroite(ligne, i, 2);
        ligne[i] = '<';
        ligne[i + 1] = '/';
        ligne[i + 2] = 'b';
        ligne[i + 3] = '>';
        decalDroite(ligne, posEt, 1);
        ligne[posEt] = '<';
        ligne[posEt + 1] = 'b';
        ligne[posEt + 2] = '>';
        posEt = -1;
      } else {
        posEt = i;
      }
    } else if (ligne[i] == '_' && ligne[i + 1] == '_') {
      if (posBa != -1) {
        decalDroite(ligne, i, 2);
        ligne[i] = '<';
        ligne[i + 1] = '/';
        ligne[i + 2] = 'b';
        ligne[i + 3] = '>';
        decalDroite(ligne, posBa, 1);
        ligne[posBa] = '<';
        ligne[posBa + 1] = 'b';
        ligne[posBa + 2] = '>';

        posBa = -1;
      } else {
        posBa = i;
      }
    }
  }
}

void static_transform(char dest[LINES][COLUMNS], char source[LINES][COLUMNS]) {
  int i = 0;
  int w = 0;
  int h = 0;
  while (source[i][0] != EOF) {
    strong_emphasis(source[i]);
    emphasis(source[i]);
    if ((h = is_header(source[i]))) {
      sprintf(dest[w++], "<h%d>\n", h);
      strcpy(dest[w++], source[i]);
      sprintf(dest[w++], "</h%d>\n", h);
    } else {
      strcpy(dest[w++], source[i]);
    }
    i++;
  }
  dest[w][0] = EOF;
}

text *dynamic_transform(text *src) {
  text *act = src;
  text *tmp;
  int h;

  while (act->content[0] != EOF) {
    strong_emphasis(act->content);
    emphasis(act->content);
    if ((h = is_header(act->content))) {
      char flemmeDeFaireAutrement[COLUMNS];
      strcpy(flemmeDeFaireAutrement, act->content);
      tmp = act->next;
      sprintf(act->content, "<h%d>\n", h);
      act->next = malloc(sizeof(text));
      act = act->next;
      strcpy(act->content, flemmeDeFaireAutrement);
      act->next = malloc(sizeof(text));
      act = act->next;
      sprintf(act->content, "</h%d>\n", h);
      act->next = tmp;
    }
    act = act->next;
  }
  return src;
}
