CC=gcc
CFLAGS=-ggdb
SRC=shell.c builtin.c hashtable.c
LIBS=-lreadline -lm

all: main

main: $(SRC)
	$(CC) $(CFLAGS) -o sush $(SRC) $(LIBS)

install:
	cp sush /usr/bin/sush

uninstall:
	rm -rf /usr/bin/sush

clean:
	rm -rf sush
