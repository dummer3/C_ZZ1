/*
 * REMPLACER LES NOMS DES FONCTIONS PAR LES VOTRES
 * DANS LES FICHIERS VOTRECODE.H et VOTRECODE.C
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "code.h"

#include "../teZZt.h"


// DEBUT DES FONCTIONS DE TESTS
BEGIN_TEST_GROUP(exo2)

// ********************************************************
//  TESTS DES FONCTIONS UTILITAIRES
// ********************************************************


TEST(HEADER) {
    char work [COLUMNS];
    int k = 0;

    strcpy(work, "une ligne sans entete");
    
    k = is_header(work);
    CHECK( 0 == k );

    strcpy(work, "# un entete de niveau 1");
    k = is_header(work);
    CHECK( 1 == k );

    strcpy(work, "#entete encore");
    k = is_header(work);
    CHECK( 1 == k );

    strcpy(work, "#");
    k = is_header(work);
    CHECK( 1 == k );

    strcpy(work, " # pas d entete");
    k = is_header(work);
    CHECK( 0 == k );

    strcpy(work, "## entete de niveau 2");
    k = is_header(work);
    CHECK( 2 == k );

    strcpy(work, "### entete de niveau 3");
    k = is_header(work);
    CHECK( 3 == k );

    // le HTML accepte les entetes jusqu a 6, on ne teste pas plus que 3 
    // et on ne limite pas a 6 non plus
}

// on cherche *texte* ou _texte_ mais il n'y en a pas
// la fonction emphasis() modifie la chaine en parametre si nécessaire
TEST(EMPHASIS_NO) {
    char origin[COLUMNS];
    char work  [COLUMNS];

    strcpy(origin, "pas de texte a detecter");
    strcpy(work, origin);
    
    emphasis(work);
    CHECK ( !strcmp( origin, work) );

    strcpy(origin, "");
    strcpy(work, origin);
    
    emphasis(work);
    CHECK ( !strcmp( origin, work) );
}

// emphase *texte* a trouver et a remplacer
TEST(EMPHASIS_STAR) {
    char res  [COLUMNS];
    char work [COLUMNS];

    strcpy(work, "* tout le texte a detecter *");
    strcpy(res , "<i> tout le texte a detecter </i>");
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "*un* peu de texte a detecter");
    strcpy(res , "<i>un</i> peu de texte a detecter");
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "un *peu de texte* a detecter");
    strcpy(res , "un <i>peu de texte</i> a detecter");
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "un peu de texte *a detecter*");
    strcpy(res , "un peu de texte <i>a detecter</i>");
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "*plusieurs* zones de texte a *detecter*");
    strcpy(res,  "<i>plusieurs</i> zones de texte a <i>detecter</i>");

    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(res, " une *etoile mais rien a detecter");
    strcpy(work, res);
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );
}

// emphase _texte_ a trouver et a remplacer
TEST(EMPHASIS_UNDER) {
    char res  [COLUMNS];
    char work [COLUMNS];

    strcpy(work, "_ tout le texte a detecter _");
    strcpy(res , "<i> tout le texte a detecter </i>");
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "_un_ peu de texte a detecter");
    strcpy(res , "<i>un</i> peu de texte a detecter");
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "un _peu de texte_ a detecter");
    strcpy(res , "un <i>peu de texte</i> a detecter");
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "un peu de texte _a detecter_");
    strcpy(res , "un peu de texte <i>a detecter</i>");
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "_plusieurs_ zones de texte a _detecter_");
    strcpy(res,  "<i>plusieurs</i> zones de texte a <i>detecter</i>");

    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(res, " un _tiret bas sans rien a detecter");
    strcpy(work, res);
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );
}

// quelques cas un peu plus compliques
TEST(EMPHASIS_HARD) {
    char res  [COLUMNS];
    char work [COLUMNS];

    strcpy(work, " toujours * rien _ mais encore");
    strcpy(res, work);
    
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "meme _si_ les symboles *sont* differents");
    strcpy(res,  "meme <i>si</i> les symboles <i>sont</i> differents");
  
    emphasis(work);
    CHECK ( !strcmp( res, work) );

    // on ne traite pas le cas ou les symboles sont imbriques
}

// essais sans **texte** ou __texte__
TEST(STRONG_EMPHASIS_NO) {
    char origin[COLUMNS];
    char work  [COLUMNS];

    strcpy(origin, "pas de texte a detecter");
    strcpy(work, origin);
    
    strong_emphasis(work);
    CHECK ( !strcmp( origin, work) );

    strcpy(origin, "");
    strcpy(work, origin);
    
    strong_emphasis(work);
    CHECK ( !strcmp( origin, work) );
}

// recherche et modification de **texte**
TEST(STRONG_EMPHASIS_STAR) {
    char res  [COLUMNS];
    char work [COLUMNS];

    strcpy(work, "** tout le texte a detecter **");
    strcpy(res , "<b> tout le texte a detecter </b>");
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "**un** peu de texte a detecter");
    strcpy(res , "<b>un</b> peu de texte a detecter");
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "un **peu de texte** a detecter");
    strcpy(res , "un <b>peu de texte</b> a detecter");
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "un peu de texte **a detecter**");
    strcpy(res , "un peu de texte <b>a detecter</b>");
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "**plusieurs** zones de texte a **detecter**");
    strcpy(res,  "<b>plusieurs</b> zones de texte a <b>detecter</b>");

    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(res, " une **double etoile mais rien a detecter");
    strcpy(work, res);
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    // on en traite pas le cas ou il y a plus de 2 étoiles comme symbole
}

// on cherche __texte__ et on modifie 
TEST(STRONG_EMPHASIS_UNDER) {
    char res  [COLUMNS];
    char work [COLUMNS];

    strcpy(work, "__ tout le texte a detecter __");
    strcpy(res , "<b> tout le texte a detecter </b>");
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "__un__ peu de texte a detecter");
    strcpy(res , "<b>un</b> peu de texte a detecter");
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "un __peu de texte__ a detecter");
    strcpy(res , "un <b>peu de texte</b> a detecter");
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "un peu de texte __a detecter__");
    strcpy(res , "un peu de texte <b>a detecter</b>");
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "__plusieurs__ zones de texte a __detecter__");
    strcpy(res,  "<b>plusieurs</b> zones de texte a <b>detecter</b>");

    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(res, " un __double tiret bas sans rien a detecter");
    strcpy(work, res);
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );
}

// quelques situations peut etre plus compliquees
TEST(STRONG_EMPHASIS_HARD) {
    char res  [COLUMNS];
    char work [COLUMNS];

    strcpy(work, " toujours ** rien __ mais encore");
    strcpy(res, work);
    
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    strcpy(work, "meme __si__ les symboles **sont** differents");
    strcpy(res,  "meme <b>si</b> les symboles <b>sont</b> differents");
  
    strong_emphasis(work);
    CHECK ( !strcmp( res, work) );

    // on ne traite pas le cas ou les symboles sont imbriques
}

// ********************************************************
//  TESTS DES FONCTIONS POUR FICHIERS STATIQUES
// ********************************************************

// lecture d'un fichier texte statique
TEST(READS, "") {

    char fichier[LINES][COLUMNS];

    static_import_text("pas_de_fichier.md", fichier );
    REQUIRE( fichier[0][0] == EOF);

    static_import_text("exemple.md", fichier );

    // nombre de lignes donnees par la commande wc
    REQUIRE( fichier[12][0] == EOF);
}

// ecriture d'un fichier texte statique a l'identique
TEST(WRITES, "") {

    char fichier[LINES][COLUMNS];

    static_import_text("exemple.md", fichier );

    FILE * file = fopen("resultats", "w");
    static_export(file, fichier);
    fclose(file);

    // la commande diff renvoie 0 si les fichiers n'ont pas de difference
    int result = system("diff exemple.md resultats");
    
    CHECK( 0 == result);
}

// lecture d un fichier texte statique et ecriture dans un autre fichier
TEST(TRANSFORMS, "") {

    char source[LINES][COLUMNS];
    char transfo[LINES][COLUMNS];

    static_import_text("exemple.md", source );

    static_transform(transfo, source);

    FILE * file = fopen("transfos", "w");
    static_export(file, transfo);
    fclose(file);

    // la commande diff renvoie 0 si les fichiers n'ont pas de difference
    int result = system("diff exemple.html transfos");
    
    CHECK( 0 == result);
}

// ********************************************************
//  TESTS DES FONCTIONS POUR FICHIERS DYNAMIQUES
// ********************************************************

// test sur la liberation memoire
// le test est fait avec valgrind mais aussi par ...
TEST(FREED) {
   text * t = NULL;

   dynamic_free(&t);

   REQUIRE ( NULL == t);
}

// lecture d un fichier texte dynamique
TEST(READD, "") {

    text * t = NULL;

    t = dynamic_import_text("pas_de_fichier.md");
    REQUIRE( NULL == t );

    t = dynamic_import_text("exemple.md");

    REQUIRE( NULL != t );

    dynamic_free(&t);
}

// lecture d un fichier texte dynamique et ecriture a l'identique
TEST(WRITED, "") {

    text * t = NULL;

    t = dynamic_import_text("exemple.md");

    FILE * file = fopen("resultatd", "w");
    dynamic_export(file, t);
    fclose(file);

    // la commande diff renvoie 0 si les fichiers n'ont pas de difference
    int result = system("diff exemple.md resultatd");

    CHECK( 0 == result);

    dynamic_free(&t);
}

// ajout de lignes a la fin d un fichier dynamique
// cela peut etre une aide pour la suite
TEST(ADDD) {
   text * t = NULL;

   dynamic_add(&t, "ligneA");
   REQUIRE ( NULL != t);
   CHECK( !strcmp( "ligneA", t->content));


   dynamic_add(&t, "ligneB");
   CHECK( !strcmp( "ligneB", t->next->content));

   dynamic_add(&t, "ligneC");
   CHECK( !strcmp( "ligneC", t->next->next->content));

   dynamic_free(&t);
}

// lecture, modification et ecriture d un fichier texte dynamique
TEST(TRASNFORMD, "") {

  text *t = NULL;
  text *d = NULL;

  t = dynamic_import_text("exemple.md");

  d = dynamic_transform(t);

  FILE *file = fopen("transfod", "w");
  dynamic_export(file, d);
  fclose(file);

  // la commande diff renvoie 0 si les fichiers n'ont pas de difference
  int result = system("diff exemple.html transfod");

  CHECK(0 == result);

  dynamic_free(&t);
  // dynamic_free(&d);
}

END_TEST_GROUP(exo2)

int main() {
  RUN_TEST_GROUP(exo2);
  return 0;
}
