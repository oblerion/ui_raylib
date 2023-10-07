#! /bin/bash

CC=clang
DSRC=src
DOBJ=build/linux64/obj
DEXEC=build/linux64
EXEC=main

all: link run

link: main.o ui.o kbd_layout.o
	$(CC) $(DOBJ)/main.o $(DOBJ)/ui.o $(DOBJ)/kbd_layout.o -g -Wall -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o $(DEXEC)/$(EXEC)

main.o: ${DSRC}/main.c
	$(CC) -c $(DSRC)/main.c -Isrc -Wall -o $(DOBJ)/main.o

ui.o: $(DSRC)/ui.c
	$(CC) -c $(DSRC)/ui.c -Isrc -Wall -o $(DOBJ)/ui.o

kbd_layout.o: $(DSRC)/kbd_layout.c
	$(CC) -c $(DSRC)/kbd_layout.c -Isrc -Wall -o $(DOBJ)/kbd_layout.o

run:
	cd $(DEXEC)
	./$(EXEC)

clean:
	rm -rf $(DOBJ)/*.o
