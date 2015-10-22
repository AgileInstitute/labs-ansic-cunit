CC := gcc
APP := bin/simtrek
TESTS := bin/testrunner

BUILDDIR := build
TESTDIR := test

OBJECTS := build/game.o build/klingon.o
CFLAGS := -ansi -std=c99
LIB := ../lib/libcunit.a
INC := -I ../include -I src

all: test

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

$(TESTS): $(OBJECTS) $(TESTDIR)/tests.o 
	@echo " *** Building $@"
	$(CC) $^ -o $(TESTS) $(LIB)

play: $(APP)
	@echo " *** Running $^"
	$(APP)

test: $(TESTS)
	@echo " *** Running $^"
	$(TESTS)

.PHONY: clean play test
