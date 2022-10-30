#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct noeud {
  int cle;
  char *inf;
  struct noeud *g;
  struct noeud *d;

} noeud_t;

void insere(noeud_t *r, noeud_t *n) {

  int alea = rand() % 100;
  if (alea % 2 == 0) {
    if (r->g == NULL) {
      r->g = n;
    } else {
      insere(r->g, n);
    }
  } else {
    if (r->d == NULL) {
      r->d = n;
    } else {
      insere(r->d, n);
    }
  }
}

noeud_t *init(int i) {
  noeud_t *n = malloc(sizeof(noeud_t));
  n->cle = i;
  n->g = NULL;
  n->d = NULL;
  return n;
}

noeud_t *rech_rec(noeud_t *r, int v, int *count) {

  noeud_t *temp;
  if (r != NULL) {
    (*count)++;
    if (r->cle == v)
      return r;
    else if ((temp = rech_rec(r->g, v, count)) != NULL)
      return temp;
    else
      return rech_rec(r->d, v, count);
  }
  return NULL;
}
noeud_t *rech(noeud_t *r, int v) {
  int i = 0;
  noeud_t *temp = rech_rec(r, v, &i);
  printf("Resultat %d trouvé au bout de %d étapes\n", v, i);
  return temp;
}

char *aff_pre(noeud_t *r) {
  char *rep = malloc(500);
  char *g_prec = NULL;
  char *d_prec = NULL;
  if (r->g != NULL && r->d != NULL) {
    g_prec = aff_pre(r->g);
    d_prec = aff_pre(r->d);
    sprintf(rep, "%d %s %s", r->cle, g_prec, d_prec);
  } else if (r->g != NULL) {
    g_prec = aff_pre(r->g);
    sprintf(rep, "%d %s", r->cle, g_prec);
  } else if (r->d != NULL) {
    d_prec = aff_pre(r->d);
    sprintf(rep, "%d %s", r->cle, d_prec);
  } else
    sprintf(rep, "%d", r->cle);
  if (g_prec != NULL)
    free(g_prec);
  if (d_prec != NULL)
    free(d_prec);
  return rep;
}

void free_n(noeud_t *r) {
  if (r->g != NULL)
    free_n(r->g);

  if (r->d != NULL)
    free_n(r->d);

  free(r);
}
char *aff_suf(noeud_t *r) {
  char *rep = malloc(500);
  char *g_prec = NULL;
  char *d_prec = NULL;
  if (r->g != NULL && r->d != NULL) {
    g_prec = aff_suf(r->g);
    d_prec = aff_suf(r->d);
    sprintf(rep, "%s %s %d", g_prec, d_prec, r->cle);
  } else if (r->g != NULL) {
    g_prec = aff_suf(r->g);
    sprintf(rep, "%s %d", g_prec, r->cle);
  } else if (r->d != NULL) {
    d_prec = aff_suf(r->d);
    sprintf(rep, "%s %d", d_prec, r->cle);
  } else
    sprintf(rep, "%d", r->cle);
  if (g_prec != NULL)
    free(g_prec);
  if (d_prec != NULL)
    free(d_prec);
  return rep;
}

char *aff_inf(noeud_t *r) {
  char *rep = malloc(500);
  char *g_prec = NULL;
  char *d_prec = NULL;
  if (r->g != NULL && r->d != NULL) {
    g_prec = aff_inf(r->g);
    d_prec = aff_inf(r->d);
    sprintf(rep, "%s %d %s", g_prec, r->cle, d_prec);
  } else if (r->g != NULL) {
    g_prec = aff_suf(r->g);
    sprintf(rep, "%s %d", g_prec, r->cle);
  } else if (r->d != NULL) {
    d_prec = aff_suf(r->d);
    sprintf(rep, "%d %s", r->cle, d_prec);
  } else
    sprintf(rep, "%d", r->cle);
  if (g_prec != NULL)
    free(g_prec);
  if (d_prec != NULL)
    free(d_prec);
  return rep;
}
int main() {
  srand(time(0));
  noeud_t *r = init(-1);
  for (int i = 0; i < 15; i++) {
    insere(r, init(i));
  }
  printf("%s\n", aff_pre(r));
  printf("%s\n", aff_inf(r));
  printf("%s\n", aff_suf(r));

  // flemme de free les 3 str

  printf("Recherche de %d ::: %d\n", 0, rech(r, 0)->cle);
  free_n(r);
  return 0;
}
