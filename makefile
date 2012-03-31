CC=gcc
CFLAGS= -g -fopenmp
TARGETS= trickOrTreat trickOrTreat_omp generateData

.PHONY: all clean

all: $(TARGETS)

clean:
	-rm -f *.o core.* $(TARGETS)