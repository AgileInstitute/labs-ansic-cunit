#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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
#endif 

extern int printf(const char *format, ...)
{
	if (mocking) {
		fprintf(stdout, "\n*** TODO build a MOCK printf(%s, ...) !!!\n", format);

#define TRY_VSPRINTF

#ifdef TRY_VSPRINTF
	va_list ap;
	char buffer[512];
           va_start(ap, format);
vsprintf(buffer, format, ap);
           va_end(ap);
	strcat(mockOutput, buffer);
#endif

#ifdef TRY_STDARGS
	va_list ap;
           int d;
           char c, *s;
	char *fmt = format;

           va_start(ap, fmt);
           while (*fmt)
	{
               switch (*fmt++) {
               case 's':              /* string */
                   s = va_arg(ap, char *);
                   printf("string %s\n", s);
                   break;
               case 'd':              /* int */
                   d = va_arg(ap, int);
                   printf("int %d\n", d);
                   break;
               case 'c':              /* char */
                   /* need a cast here since va_arg only
                      takes fully promoted types */
                   c = (char) va_arg(ap, int);
                   printf("char %c\n", c);
                   break;
               }
	}
           va_end(ap);
#endif
	}
	else
	{
		fprintf(stdout, "\n*** TODO build a pass-through to fprintf(stdout, format=%s, ...) !!!\n", format);
		return -1;
	}
	return 0;
}

#endif 

extern void mocks_setup() {
	mocking = 1;
#if MOCK_PRINTF
	mocks_resetOutput();
#endif
}
extern void mocks_teardown() {
	mocking = 0;
}

extern void mocks_verboseAssertStringEquals(char* expected, char* actual)
{
#if MOCKS_VERBOSE
	if (strcmp(expected, actual))
	{
		fprintf(stderr,
		"*** MOCKS: expected [%s] got [%s] !!!\n", expected, actual);
	}
#endif
}

extern void mocks_verboseAssertIntEquals(int expected, int actual)
{
#if MOCKS_VERBOSE
	if (expected != actual)
	{
		fprintf(stderr,
		"*** MOCKS: expected %d got %d !!!\n", expected, actual);
	}
#endif
}
