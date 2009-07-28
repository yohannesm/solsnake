VALGRIND ?= valgrind
DOXYGEN ?= doxygen
CC = g++
EXTRA_CPPFLAGS += -g -ggdb -ansi -pedantic -Wall
TEST_LDFLAGS = -lcppunit -ldl
TEST_CPPFLAGS = -DTEST
EXECUTABLE = main.app
DOXYFILE = Doxyfile

all: clean docs $(EXECUTABLE) $(TEST_EXEC)

$(EXECUTABLE): main.c++
	$(CC) $(EXTRA_CPPFLAGS) $(TEST_LDFLAGS) $(TEST_CPPFLAGS) $< -o $@

docs: $(DOXYFILE)
	doxygen Doxyfile >/dev/null 2>&1

clean:
	-rm -f $(EXECUTABLE) $(TEST_EXEC) html/*
	-rmdir html >/dev/null 2>&1

distclean: clean
	rm -f $(DOXYFILE)

$(DOXYFILE):
	$(DOXYGEN) -g
	sed -i 's/^EXTRACT_ALL\([ \t]*=[ \t]*\).*/EXTRACT_ALL\1YES/g' $@
	sed -i 's/^EXTRACT_PRIVATE\([ \t]*=[ \t]*\).*/EXTRACT_PRIVATE\1YES/g' $@
	sed -i 's/^EXTRACT_STATIC\([ \t]*=[ \t]*\).*/EXTRACT_STATIC\1YES/g' $@
	sed -i 's/^GENERATE_LATEX\([ \t]*=[ \t]*\).*/GENERATE_LATEX\1NO/g' $@
