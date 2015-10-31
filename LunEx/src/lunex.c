#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "lunex.h"

/*
** STOP!  You are not to alter this file.  It represents 3rd-party software.
*/

long currentPrice(char* symbol) {
	srand(time(0));

	sleep(5);
	if (rand() % 100 > 80) {
		return -1; /* sunspots! good old sloppy error reporting */
	}

	return 42 + (rand() % 24);
}
