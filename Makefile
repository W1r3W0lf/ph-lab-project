
CC=gcc
CFLAGS= -lpthread -O3

merge-run: merge.o
	$(CC) -o $@ main.c merge.o $(CFLAGS)

merge.o:
	$(CC) -c merge.c merge.h  $(CFLAGS)

clean:
	rm merge.o merge-run merge.h.gch

