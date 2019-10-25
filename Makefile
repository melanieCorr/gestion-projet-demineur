CC=gcc
CFLAGS=-W -g -Wall -O3
PROGNAME=demineur
VPATH=include:src
RM=rm -rf

all: $(PROGNAME)
	$(RM) bin
	mkdir bin
	rm -f *.o
	mv $(PROGNAME) ./bin

$(PROGNAME): game.o helper.o helper.h
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	$(RM) bin
