#ifndef MOCKS_HEADER
#define MOCKS_HEADER

#define MOCKS_VERBOSE 1

#define MOCK_PRINTF 1
#define COMPILER_REPLACES_SIMPLE_PRINTF_WITH_PUTS 1

extern void mocks_setup();
extern void mocks_teardown();

#if MOCK_PRINTF
extern void mocks_resetOutput();
extern char* mocks_allOutput();
#endif

extern void mocks_verboseAssertStringEquals(char* expected, char* actual);
extern void mocks_verboseAssertIntEquals(int expected, int actual);

#endif
