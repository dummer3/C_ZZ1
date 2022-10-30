#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST(F, A, ...)                                                        \
  fprintf(F, "%s(%s) ::: %.2f\n", #A, #__VA_ARGS__, (double)(A(__VA_ARGS__)))

typedef enum ope { NONE = -1, ID, SIN, COS, LOG, EXP } OP;
static const OP op_map[] = {ID, SIN, COS, LOG, EXP};
static const char *op_name[] = {"ID", "SIN", "COS", "LOG", "EXP"};
const char *OPER_NAMES[] = {"x", "sin", "cos", "log", "exp", NULL};

typedef enum ope2 { MUL = '*', ADD, ZZZ, SOU, YYY, DYV } OP2;
static const OP op_map2[] = {MUL, ADD, SOU, DYV};
const char OPER_NAMES2[] = {'*', '+', '-', '/', '\0'};

double id(double b) { return b; }

double mul(double a, double b) { return a * b; }
double add(double a, double b) { return a + b; }
double sou(double a, double b) { return a - b; }
double dyv(double a, double b) { return a / b; }

double (*op_fonc[])(double) = {id, sin, cos, log, exp};
double (*op_fonc2[])(double, double) = {mul, add, NULL, sou, NULL, dyv};

typedef struct pile {
  double tab[256];
  int taille;
} pile_t;

void empiler(pile_t *p, double d) {
  if (p->taille < 256) {
    p->tab[p->taille] = d;
    (p->taille)++;
  } else {
    fprintf(stderr, "PILE PLEINE\n");
    exit(-1);
  }
}

double look_depiler(pile_t *p) {
  if (p->taille > 0) {
    (p->taille)--;
  } else {
    fprintf(stderr, "PILE DEJA VIDE\n");
    exit(-1);
  }
  return p->tab[(p->taille)];
}

pile_t *initPile() {
  pile_t *p = malloc(sizeof(pile_t));
  p->taille = 0;
  return p;
}

OP identification(char *s) {
  int i = 0;
  while (OPER_NAMES[i]) {
    if (!strcmp(s, OPER_NAMES[i])) {
      return op_map[i];
    }
    i++;
  }
  return NONE;
}
OP2 identification2(char s) {
  int i = 0;
  while (OPER_NAMES2[i]) {
    if (s == OPER_NAMES2[i]) {
      return op_map2[i];
    }
    i++;
  }
  return YYY;
}

double evalf(double f, OP o) { return op_fonc[o](f); }
double evalf2(double f, double l, OP2 o) { return op_fonc2[o - '*'](f, l); }

void calcul(float a, float b, float delta, OP o, FILE *file) {
  for (double i = a; i <= b; i += delta) {
    fprintf(file, "valeur de %s(%.2f) ::: %.2f\n", op_name[o], i, evalf(i, o));
  }
}

void affichageOperation() {
  int i = 0;
  while (OPER_NAMES[i]) {
    printf("| %d :: %-6s |\n", i, OPER_NAMES[i]);
    i++;
  }
  printf("\n\n");
}
void my_fgets(char *s, int length, FILE *stream) {
  fgets(s, length, stream);
  for (int i = 0; i < length; i++) {
    if (*(s + i) == '\n') {
      *(s + i) = '\0';
    }
  }
}

void calculatrice2() {
  OP o;
  char buffer[255], a[25];
  double min, max, delta;
  FILE *F;
  do {
    printf("Quel calcul voulez vous ?\nENTER : ");
    my_fgets(buffer, 255, stdin);
    sscanf(buffer, "%s", a);
    o = identification(a);

    if (o == -1) {
      printf("ERREUR ce calcul n'est pas pris en compte, vous avez le choix "
             "entre:\n");
      affichageOperation();
    }
  } while (o == -1);
  do {
    printf("Donner les informations suivantes comme demandé : \nMin Max "
           "Delta\nEnter : ");
    my_fgets(buffer, 255, stdin);
    sscanf(buffer, "%lf %lf %lf", &min, &max, &delta);
  } while (max < min || delta > max - min || !delta);
  do {
    printf("Donner le nom du fichier:\nEnter : ");
    my_fgets(buffer, 255, stdin);
    F = fopen(buffer, "w");
  } while (!F);
  calcul(min, max, delta, o, F);
  printf("Calcul Fini\n");
}

void calculExpression(FILE *F, char *expr) {
  char copy[500];
  strcpy(copy, expr);
  char temp[20];
  pile_t *pile = initPile();
  double a, b;
  do {
    sscanf(expr, "%s %[^\n]s", temp, expr);
    if (atol(temp)) {
      empiler(pile, atol(temp));
      printf("emp %lf\n", pile->tab[pile->taille - 1]);
    } else if (identification(temp) != NONE && pile->taille > 0) {
      a = look_depiler(pile);
      empiler(pile, evalf(a, (identification(temp))));
      printf("%lf\n", pile->tab[pile->taille - 1]);
    } else if (identification2(temp[0]) != YYY && pile->taille > 1) {
      b = look_depiler(pile);
      a = look_depiler(pile);
      empiler(pile, evalf2(a, b, (identification2(temp[0]))));
      printf("%lf %c %lf = %lf\n", a, (identification2(temp[0])), b,
             pile->tab[pile->taille - 1]);
    } else {
      fprintf(stderr, "EXPR NON RECONNUE\n");
      exit(-1);
    }

  } while (strcmp(expr, temp));
  if (pile->taille == 1) {
    fprintf(F, "RESULTAT de %s :: %lf\n", copy, pile->tab[0]);
  } else {
    fprintf(stderr, "EXPR MAL FORMEE\n");
    exit(-1);
  }
}
void calculatrice() {
  char buffer[500], temp[255];
  FILE *F;
  do {
    printf("Quel calcul voulez vous ?\nENTER : ");
    my_fgets(buffer, 255, stdin);
  } while (strlen(buffer) == 0);

  do {
    printf("Donner le nom du fichier:\nEnter : ");
    my_fgets(temp, 255, stdin);
    F = fopen(temp, "w");
  } while (!F);
  calculExpression(F, buffer);
  printf("Calcul Fini\n");
  fclose(F);
}

int main() {
  calculatrice();
  calculatrice2();
  return 0;
}
