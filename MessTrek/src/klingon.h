#ifndef KLINGON_HEADER
#define KLINGON_HEADER

#include <stdlib.h>

typedef struct Klingon {
	int distance;
	int energy;
	int destroyed;
} Klingon;


void initKlingon(Klingon *k);

#endif
