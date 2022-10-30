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
BEGIN_TEST_GROUP(exo1)


TEST(INIT1, "initialisation tab statique") {
	char tab[5];
    
    init(tab, 5);
    CHECK(0 == tab[0]);
    CHECK(0 == tab[1]);
    CHECK(1 == tab[2]);
    CHECK(1 == tab[2]);
    CHECK(1 == tab[3]);
    CHECK(1 == tab[4]);
}

TEST(INIT2, "initialisation tab dynamique") {
	char * tab = NULL;
    
    tab = init(tab, 5);

    REQUIRE( NULL != tab);

    CHECK(0 == tab[0]);
    CHECK(0 == tab[1]);
    CHECK(1 == tab[2]);
    CHECK(1 == tab[3]);
    CHECK(1 == tab[4]);

    free(tab);
}

TEST(AFF1, "") {
	char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");

	char tab[10];
    init(tab, 10);
    //affichage(stdout, tab, 10);
    affichage(file, tab, 10);
    fclose(file);

    CHECK( !strcmp("2 3 4 5 6 7 8 9", buffer ) );

}	

TEST(SUPP2, "") {
	char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");

	char tab [20];
    init(tab, 20);
    suppMultiple(tab, 20, 2);
    // affichage(stdout, tab, 20);
    affichage(file, tab,   20);
    fclose(file);

    CHECK( !strcmp("2 3 5 7 9 11 13 15 17 19", buffer ) );

    
}	

TEST(SUPP3, "") {
	char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");

	char tab [20];
    init(tab, 20);
    suppMultiple(tab, 20, 3);
    // affichage(stdout, tab, 20);
    affichage(file, tab,   20);

    fclose(file);

    CHECK( !strcmp("2 3 4 5 7 8 10 11 13 14 16 17 19", buffer ) );

    
}	

TEST(SUPP2_3, "") {
	char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");

	char tab [20];
    init(tab, 20);
    suppMultiple(tab, 20, 2);
    suppMultiple(tab, 20, 3);
    //affichage(stdout, tab, 20);
    affichage(file, tab,   20);

    fclose(file);
    CHECK( !strcmp("2 3 5 7 11 13 17 19", buffer ) );
}


TEST(PROCHAIN, "") {
	
	char tab [20];
    init(tab, 20);
    suppMultiple(tab, 20, 2);
    suppMultiple(tab, 20, 3);
    
    CHECK(  3 == prochainNombre(tab, 20,  2));
    CHECK(  5 == prochainNombre(tab, 20,  3));
    CHECK(  5 == prochainNombre(tab, 20,  4));
    CHECK(  7 == prochainNombre(tab, 20,  5));
    CHECK( 11 == prochainNombre(tab, 20,  7));
    CHECK( 13 == prochainNombre(tab, 20, 11));
    CHECK( 17 == prochainNombre(tab, 20, 13));
    CHECK( 17 == prochainNombre(tab, 20, 15));
    CHECK( 19 == prochainNombre(tab, 20, 17));
    CHECK( -1 == prochainNombre(tab, 20, 19));	
    CHECK( -1 == prochainNombre(tab, 20, 30));	
    
}

TEST(FINAL1, "") {
	char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
	int nombre;
	
	nombre =  listeNombrePremiers(file , 10);
    fclose(file);

	CHECK( 4 == nombre );
	CHECK( !strcmp("2 3 5 7", buffer ) );

   
}

TEST(FINAL2, "") {
	char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
	int nombre;
	
    nombre =  listeNombrePremiers(file , 20);
    fclose(file);

    CHECK( 8 == nombre );
    CHECK( !strcmp("2 3 5 7 11 13 17 19", buffer ) );

    
}

TEST(FINAL3, "") {
	char buffer[1024];
    FILE * file = fmemopen(buffer, 1024, "w");
	int nombre;
	
    nombre =  listeNombrePremiers(file , 100);
    fclose(file);
    // je vais tester le tableau 
    CHECK( 25 == nombre );
}

TEST(FINAL4, "") {
	char buffer[1024];
	//  c'est encore assez grand
    FILE * file = fmemopen(buffer, 1024, "w");
	int nombre;
	
    nombre =  listeNombrePremiers(file , 1000);
    fclose(file);
    
    // je vais tester la valeur et le tableau :-)
    printf("%d", nombre);
    
    
}

END_TEST_GROUP(exo1)


int main() {
    RUN_TEST_GROUP(exo1); 
 
   return 0;
}

