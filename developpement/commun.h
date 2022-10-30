#ifndef COMMUN_H
#define COMMUN_H

#define DEBUG

#include <string.h>

#ifdef DEBUG
#define LOG(A) printf A
#else
#define LOG(A)
#endif

extern int ERROR;

#define ERROR_OK 0
#define ERROR_LIST_ALLOC 1
#define ERROR_FILE 1

#endif
