CC = g++
CFLAGS = -Wextra -Wall -Wvla -std=c++14 -g
CPPFILES = ikea.cpp product.cpp
HFILES = product.h
CODEFILES = $(CPPFILES) $(HFILES) Makefile

# All Target
all: ex2

# Exceutables
ex2: $(CPPFILES) $(HFILES)
	$(CC) $(CFLAGS) $(CPPFILES) -o ex2

# Other Targets
clean:
	-rm -f *.o ex2 ex2.tar

# tar
tar:
	tar -cf ex2.tar $(CODEFILES)

