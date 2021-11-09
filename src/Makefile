CC=gcc
CFLAGS=-ggdb
SRC=shell.c builtin.c hashtable.c datetime.c
LIBS=-lreadline -lm

all: main

main: $(SRC)
	$(CC) $(CFLAGS) -o sush $(SRC) $(LIBS)

install:
	cp sush /usr/bin/sush
	cp inputrc /etc/inputrc

uninstall:
	rm -rf /usr/bin/sush

clean:
	rm -rf sush
