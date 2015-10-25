#include <stdio.h>

char mockOutput[256];


extern int printf (__const char *__restrict __format, ...)
{
	fprintf(stdout, "MOCKED!");
	fprintf(stderr, "MOCKED!");
	return 0;
}
