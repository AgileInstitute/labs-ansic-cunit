#include <stdio.h>

/*
ifdef Ubuntu for puts
why is printf becoming puts? Goog!
*/

char mockOutput[256];

extern int puts(const char *myString) {
	fprintf(stdout, "MOCKED puts!");
	fprintf(stderr, "MOCKED puts!");
}

extern int printf (__const char *__restrict __format, ...)
{
	fprintf(stdout, "MOCKED printf!");
	fprintf(stderr, "MOCKED printf!");
	return 0;
}
