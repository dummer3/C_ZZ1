#ifndef LISTE_H
#define LISTE_H

typedef struct cell_s {
  char key[30];
  int value;
  struct cell_s *nk, *nv;
} cell_t;

typedef struct list_s {
    cell_t * key;
    cell_t * value;
} list_t;

void initList(list_t * plist);
void displayByKey(list_t list);
void displayByValue(list_t list);
int insert(list_t * plist, char * nom, int note);
void freeList(list_t *plist);

#endif
