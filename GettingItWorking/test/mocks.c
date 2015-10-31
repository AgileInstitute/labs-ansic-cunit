#include <stdio.h>
#include <string.h>

#include "mocks.h"

/*
** NOTE:  Not really assertions (they don't make the tests fail)
** but are useful with CUnit ..._EQUAL() assertions which don't display actual.
*/
extern void mocks_verboseAssertStringEquals(char* expected, char* actual)
{
	if (strcmp(expected, actual))
	{
		fprintf(stderr,
		"\n*** MOCKS: expected [%s] got [%s]!!! ***\n",
		expected, actual);
	}
}

extern void mocks_verboseAssertIntEquals(int expected, int actual)
{
	if (expected != actual)
	{
		fprintf(stderr,
		"\n*** MOCKS: expected %d got %d!!! ***\n",
		expected, actual);
	}
}


