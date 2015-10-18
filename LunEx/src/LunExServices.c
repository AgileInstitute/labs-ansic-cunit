#include <stdlib.h>
#include <unistd.h>

#include "LunExServices.h"

static double truncate(double original) {
	long y = (long) (original * 10000);
	return (double) y / 10000;
}

static int initialized = 0;

double currentPrice(char* symbol) {
	if (!initialized) srand(time(0));

	sleep(5);
	if (rand() % 100 > 80) {
		return -1; /* good old sloppy error reporting */
	}

	double currentPrice = 42.0 + rand() * 2.1;

	return truncate(currentPrice);
}
