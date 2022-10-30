#ifndef HISTO_H
#define HISTO_H

#include "liste.h"

#define HISTOSIZE 21
typedef int histogram_t[HISTOSIZE];

void computeHisto(histogram_t h, list_t l);
void displayHisto(histogram_t h);
int maxHisto(histogram_t h);
float meanHisto(histogram_t h);
int countHisto(histogram_t h);

#endif
