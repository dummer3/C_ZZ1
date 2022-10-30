#include "code.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

char devinette[255] = "JEDETESTELEC";

void majuscules(char *s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s += 'A' - 'a';
    s++;
  }
}

char *tab[26] = {"2",   "22", "222", "3",   "33", "333", "4",   "44",  "444",
                 "5",   "55", "555", "6",   "66", "666", "7",   "77",  "777",
                 "777", "8",  "88",  "888", "9",  "99",  "999", "9999"};

char *tab2[26] = {"2",   "2*2", "3*2", "3",   "2*3", "3*3", "4",   "2*4", "3*4",
                  "5",   "2*5", "3*5", "6",   "2*6", "3*6", "7",   "2*7", "3*7",
                  "4*7", "8",   "2*8", "3*8", "9",   "2*9", "3*9", "4*9"};

char tab3[26] = {' ', ' ', 'A', 'D', 'G', 'J', 'M', 'P', 'T', 'W'};

void multitap1(char *d, char *s) {
  majuscules(s);
  d[0] = 0;
  while (*s) {
    strcat(d, tab[(*s) - 'A']);
    s++;
    if (*s)
      strcat(d, " ");
  }
  strcat(d, "\0");
}

void multitap2(char *s) {
  char d[255] = "";
  char *t = s;
  majuscules(s);
  while (*t) {
    strcat(d, tab2[(*t) - 'A']);
    t++;
  }
  strcat(d, "\0");
  strcpy(s, d);
  printf("@%s@\n", s);
}

void antitap1(char *d, char *s) {
  majuscules(s);
  d[0] = 0;
  int i = 0;
  while (*s) {
    d[i] = tab3[*s - '0'];
    while (*(++s) != 0 && *s != ' ') {
      d[i]++;
    }
    ++s;
    i++;
  }
  d[i] = 0;
  printf("@%s@\n", d);
}

void antitap2(char *s) {
  char d[255] = "";
  char a, b;
  int i = 0;
  char *t = s;
  while (*t) {
    if (t[1] == '*') {
      sscanf(t, "%c%*c%c", &a, &b);
      d[i] = tab3[b - '0'] + a - '0' - 1;
      t += 3;
    } else {
      d[i] = tab3[*t - '0'];
      ++t;
    }
    i++;
  }
  d[i] = 0;
  strcpy(s, d);
  printf("@%s@\n", s);
}

char *sms(char *nom) {
  char s[255], d[255], *result = malloc(2000);
  FILE *F = fopen(nom, "r");
  if (F != NULL) {
    while (fgets(s, 255, F)) {
      multitap1(s, d);
      strcat(result, d);
    }
    fclose(F);
    return result;
  } else {
    printf("ERROR CAN T OPEN FILE\n");
    exit(-1);
  }
}
