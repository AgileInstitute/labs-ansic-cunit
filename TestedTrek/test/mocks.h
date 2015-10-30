#ifndef MOCKS_HEADER
#define MOCKS_HEADER

#define MOCK_PRINTF 1
#define COMPILER_REPLACES_SIMPLE_PRINTF_WITH_PUTS 1

extern void mocks_setup();
extern void mocks_teardown();

#if MOCK_PRINTF
extern void mocks_resetOutput();
extern char* mocks_allOutput();
#endif

#endif
