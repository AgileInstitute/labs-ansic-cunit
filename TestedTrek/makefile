CC := gcc
APP := bin/simtrek
TESTS := bin/testrunner

BUILDDIR := build
TESTDIR := test
 
OBJECTS := build/game.o build/klingon.o
CFLAGS := -ansi
LIB := -l ../../stuff/lib/libcunit.so
INC := -I ../../stuff/include

$(BUILDDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(TESTDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " *** Cleaning"; 
	$(RM) $(BUILDDIR)/*.o $(TESTDIR)/*.o $(APP) $(TESTS)

$(APP): $(OBJECTS) $(BUILDDIR)/simtrek.o
	@echo " *** Building $@"
	$(CC) $^ -o $(APP) $(LIB)

$(TESTS): $(TESTDIR)/tests.o $(OBJECTS)
	@echo " *** Building $@"
	$(CC) $^ $(LIB) -o $(TESTS)

play: $(APP)
	@echo " *** Running $^"
	$(APP)

test: $(TESTS)
	@echo " *** Running $^"
	$(TESTS)

.PHONY: clean play test
