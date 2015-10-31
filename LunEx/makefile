CC := gcc
TESTS := bin/testrunner

BUILDDIR := build
TESTDIR := test

OBJECT_TO_TEST := build/stock_quote.o 
OBJECT_TO_MOCK := build/lunex.o
CFLAGS := -O0 -ansi -std=c99
LIB := -L ../lib ../lib/libcunit.a 
INC := -I ../include -I src

all: clean test

$(BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " *** Cleaning";
	$(RM) $(BUILDDIR)/*.o $(TESTDIR)/*.o $(TESTS)

$(TESTS): $(TESTDIR)/mocks.o $(OBJECT_TO_TEST) $(OBJECT_TO_MOCK) $(TESTDIR)/tests.o 
	@echo " *** Building $@"
	$(CC) $^ -o $(TESTS) $(LIB)

test: $(TESTS)
	@echo " *** Running $^"
	$(TESTS)

.PHONY: clean test
