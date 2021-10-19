

CC=gcc
CFLAGS= -lpthread
DEPS =
OBJ = merge.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $& $< $(CFLAGS)

merge:
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm merge $(OBJ)


