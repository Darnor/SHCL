LIBRARY = -lSHCL
OPTIMIZE_FLAG = -O3
WARNING_FLAGS = -Wall -Wextra -Wconversion -Werror
PEDANTIC_FLAGS = -pedantic -pedantic-errors
CPP_FLAGS = -std=c++1y $(OPTIMIZE_FLAG) $(WARNING_FLAGS) $(PEDANTIC_FLAGS)
C_FLAGS = $(OPTIMIZE_FLAG) $(WARNING_FLAGS) $(PEDANTIC_FLAGS)

.PHONY:	all clean

all:	cppexample cexample

cppexample:	example.cpp
	g++ $(CPPFLAGS) $^ -o $@ $(LIBRARY)

cexample:	example.c
	gcc $(CFLAGS) $^ -o $@ $(LIBRARY)

clean:
	rm cppexample cexample

