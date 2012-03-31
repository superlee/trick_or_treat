CC=gcc
CFLAGS= -g -fopenmp
TARGETS= trickOrTreat trickOrTreat_omp

.PHONY: all clean

all: $(TARGETS)

clean:
	-rm -f *.o core.* $(TARGETS)