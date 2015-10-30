#include <stdio.h>

#include "mocks.h"
/* #define MOCKS_VERBOSE 1 if you need more information */

int mocking = 1;

#if MOCK_PRINTF

char mockOutput[512];
extern void mocks_resetOutput() {
	mockOutput[0] = '\0';
}
extern char* mocks_allOutput() {
#if MOCKS_VERBOSE
	fprintf(stdout, "\n*** mocks_allOutput() returning [%s]\n", mockOutput);
#endif

	return mockOutput;
}

#if COMPILER_REPLACES_SIMPLE_PRINTF_WITH_PUTS

extern int puts(const char *myString) {
	if (mocking) {
		strcat(mockOutput, myString);
		strcat(mockOutput, "\n");	/* mimic puts() correctly */
	}
	else
	{
		return fputs(myString, stdout);
	}
	return 0;
}
#endif COMPILER_REPLACES_SIMPLE_PRINTF_WITH_PUTS

extern int printf(const char *format, ...)
{
	if (mocking) {
		fprintf(stdout, "\n*** TODO build a MOCK printf(%s, ...) !!!\n", format);
	}
	else
	{
		fprintf(stdout, "\n*** TODO build a pass-through to fprintf(stdout, format=%s, ...) !!!\n", format);
		return -1;
	}
	return 0;
}

#endif MOCK_PRINTF

extern void mocks_setup() {
	mocking = 1;
#if MOCK_PRINTF
	mocks_resetOutput();
#endif
}
extern void mocks_teardown() {
	mocking = 0;
}

