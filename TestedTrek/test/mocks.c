#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "mocks.h"

int mocking = 1;

#if MOCK_RAND
static int rand_index = 0;
static int rand_defaults[1] = { 0 };
static int rand_count = 1;
static int *rand_numbers = &rand_defaults;

void mocks_setRand(int *mock_rand_numbers, int count) {
	rand_numbers = mock_rand_numbers;
	rand_count = count;
}

int rand() {
	if (rand_index == rand_count)
		rand_index = 0;

	return rand_numbers[rand_index++];
}
#endif

#if MOCK_PRINTF || MOCK_PUTS

static char mockOutput[512];

void writeToMockOutput(const char *message) {
#if MOCKS_VERBOSE
	fprintf(stderr, "\n*** MOCKS: writeToMockOutput(%s) ***\n", message);
#endif
	strcat(mockOutput, message);
}
extern void mocks_resetOutput() {
	mockOutput[0] = '\0';
}
extern char* mocks_allOutput() {
#if MOCKS_VERBOSE
	fprintf(stderr, "\n*** MOCKS: mocks_allOutput() returning [%s] ***\n", mockOutput);
#endif

	return mockOutput;
}

#if MOCK_PUTS

extern int puts(const char *myString) {
	if (mocking) {
		writeToMockOutput(myString);
		writeToMockOutput("\n"); /* mimic puts() correctly */
		return 0;
	}
	else
	{
		return fputs(myString, stdout);
	}
}

#endif 

static char mockPrintfBuffer[512];
extern int printf(const char *format, ...)
{
	mockPrintfBuffer[0] = '\0';

	/* write to buffer */
	va_list ap;
        va_start(ap, format);
	vsprintf(mockPrintfBuffer, format, ap);
        va_end(ap);

	if (mocking) {
		writeToMockOutput(mockPrintfBuffer);
		return 0;
	}
	else
	{
		return fprintf(stdout, "%s", mockPrintfBuffer);
	}
}

#endif 

extern void mocks_setup() {
	mocking = 1;
#if MOCK_PRINTF || MOCK_PUTS
	mocks_resetOutput();
#endif
#if MOCK_RAND
	mocks_setRand(rand_defaults, 1);
#endif
}
extern void mocks_teardown() {
	mocking = 0;
}

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
