CC := gcc
APP := bin/simtrek
TESTS := bin/testrunner

BUILDDIR := build
TESTDIR := test

OBJECTS := build/game.o build/klingon.o
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
	$(RM) $(BUILDDIR)/*.o $(TESTDIR)/*.o $(APP) $(TESTS)

$(APP): $(OBJECTS) $(BUILDDIR)/simtrek.o
	@echo " *** Building $@"
	$(CC) $^ -o $(APP) 

$(TESTS): $(TESTDIR)/mocks.o $(OBJECTS) $(TESTDIR)/tests.o 
	@echo " *** Building $@"
	$(CC) $^ -o $(TESTS) $(LIB)

play: $(APP)
	@echo " *** Running $^"
	$(APP)

test: $(TESTS)
	@echo " *** Running $^"
	$(TESTS)

.PHONY: clean play test
