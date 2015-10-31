#ifndef MOCKS_HEADER
#define MOCKS_HEADER

/* #define MOCKS_VERBOSE 1 if you need more information */

#define MOCK_RAND 1

#define MOCK_PRINTF 1
/*
** NOTE: (Ubuntu) gcc will replace--at COMPILE TIME!--a simple printf with puts
*/
#define MOCK_PUTS 1

extern void mocks_setup();
extern void mocks_teardown();

#if MOCK_PRINTF || MOCK_PUTS
extern void mocks_resetOutput();
extern char* mocks_allOutput();
#endif

#if MOCK_RAND
extern void mocks_setRand(int mock_rand_numbers[], int count);
#endif

extern void mocks_verboseAssertStringEquals(char* expected, char* actual);
extern void mocks_verboseAssertIntEquals(int expected, int actual);

#endif
