CC=gcc
CFLAGS= -g -fopenmp
TARGETS= trickOrTreat 

.PHONY: all clean

all: $(TARGETS)

clean:
	-rm -f *.o core.* $(TARGETS)