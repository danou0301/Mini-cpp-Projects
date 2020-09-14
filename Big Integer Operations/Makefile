CC= g++
CFLAGS= -c -Wvla -Wall -Wextra -std=c++14 -g
CODEFILES= ex1.tar big_integer.cpp my_set.cpp big_integer.h my_set.h Makefile
TESTINT= testint
TESTSET= testset

# All Target
all: my_set.o big_integer.o my_set_tester.o big_int_tester.o
	g++ my_set.o big_integer.o my_set_tester.o -o testset
	g++ big_integer.o big_int_tester.o -o testint

# Exceutables

testset: my_set.o big_integer.o my_set_tester.o
	g++ my_set.o big_integer.o my_set_tester.o -o testset && ./testset

testint: big_integer.o big_int_tester.o
	g++ big_integer.o big_int_tester.o -o testint && ./testint

# Object Files

my_set.o: my_set.cpp my_set.h
	$(CC) $(CFLAGS) my_set.cpp

big_integer.o: big_integer.cpp big_integer.h
	$(CC) $(CFLAGS) big_integer.cpp

my_set_tester.o: my_set_tester.cpp
	$(CC) $(CFLAGS) my_set_tester.cpp

big_int_tester.o: big_int_tester.cpp
	$(CC) $(CFLAGS) big_int_tester.cpp

# Other Targets
clean:
	-rm -f *.o testset testint

# Things that aren't really build targets
.PHONY: clean