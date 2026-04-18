########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -std=c90
LIBS = -lstack -L.
EJS = p4_e1 
########################################################
OBJECTSP4E1 = p4_e1.o radio.o music.o bstree.o list.o

########################################################

all: $(EJS)

.PHONY: all clean clear run

p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4E1)



########################################################

p4_e1.o: p4_e1.c music.h radio.h bstree.h
	$(CC) $(CFLAGS) -c p4_e1.c

music.o: music.c music.h 
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

bstree.o: bstree.c bstree.h
	$(CC) $(CFLAGS) -c bstree.c


########################################################

clear:
	rm -rf *.o $(EJS) 

run:
	@echo ">>>>>>Running p4_e1"
	./p4_e1 data_music_10 8 normal
	./p4_e1 data_music_10 8 sorted

	
runv:
	
	@echo ">>>>>>Running p4_e1 with valgrind"
	valgrind --leak-check=full ./p4_e1 data_music_10 8 normal
	valgrind --leak-check=full ./p4_e1 data_music_10 8 sorted