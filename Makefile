

CC=gcc
CFLAGS= -lpthread
DEPS =



merge-run: merge.o
	$(CC) -o $@ main.c merge.o -lpthread -g

merge.o:
	$(CC) -c merge.c merge.h -g


clean:
	rm merge.o merge-run merge.h.gch


