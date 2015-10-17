#ifndef KLINGON_HEADER
#define KLINGON_HEADER


#include <cstdlib>


struct Klingon {
	int distance = 100 + rand() % 4000;
	int energy = 1000 + rand() % 2000;
	int destroyed = 0;
};

#endif
