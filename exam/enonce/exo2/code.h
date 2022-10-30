#ifndef CODE_EXO2
#define CODE_EXO2

#include <stdio.h>

#define LINES   100
#define COLUMNS 1024

// structure pour la manipulation "dynamique" de fichiers
typedef struct line {
	char content[COLUMNS];
	struct line * next;
} text;

// fonctions utilitaires
void strong_emphasis(char * );
void emphasis       (char * );
int  is_header      (char *);

// fonction pour la manipulation statique de fichiers
// il faut choisir entre les fichiers statiques ou dynamiques
void static_import_text(char*  , char [LINES][COLUMNS]);
void static_export     (FILE * , char [LINES][COLUMNS]);
void static_transform  (char [LINES][COLUMNS], char [LINES][COLUMNS]);

// fonctions pour la manipulation dynamique de fichiers
// il faut choisir entre les fichiers statiques ou dynamiques
text * dynamic_import_text(char * nom);
void   dynamic_export     (FILE * , text *);
void   dynamic_add     (text **, char *);
text * dynamic_transform  (text * );
void   dynamic_free       (text ** );

#endif