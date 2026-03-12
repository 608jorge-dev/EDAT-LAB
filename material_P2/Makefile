########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic
EJS = p2_e1 p2_e2a p2_e2b p2_e3
########################################################
OBJECTSP2E1 = p2_e1.o music.o radio.o
OBJECTSP2E2A = p2_e2a.o radio.o music.o
OBJECTSP2E2B = p2_e2b.o radio.o music.o
OBJECTSP2E3 = p2_e3.o radio.o music.o
########################################################

all: $(EJS) clear

p2_e1: $(OBJECTSP2E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2E1) -lstack -L.

p2_e2a: $(OBJECTSP2E2A)
	$(CC) $(CFLAGS) -o p2_e2a $(OBJECTSP2E2A) -lstack -L.

p2_e2b: $(OBJECTSP2E2B)
	$(CC) $(CFLAGS) -o p2_e2b $(OBJECTSP2E2B) -lstack -L.

p2_e3: $(OBJECTSP2E3)
	$(CC) $(CFLAGS) -o p2_e3 $(OBJECTSP2E3) -lstack -L.

p2_e1.o: p2_e1.c 
	$(CC) $(CFLAGS) -c p2_e1.c

p2_e2a.o: p2_e2a.c music.h radio.h
	$(CC) $(CFLAGS) -c p2_e2a.c

p2_e2b.o: p2_e2b.c music.h radio.h
	$(CC) $(CFLAGS) -c p2_e2b.c
	
p2_e3.o: p2_e3.c music.h radio.h
	$(CC) $(CFLAGS) -c p2_e3.c

music.o: music.c music.h 
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e1"
	./p2_e1 radio.txt
	@echo ">>>>>>Running p2_e2a"
	./p2_e2a playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e2b"
	./p2_e2b playlistA.txt playlistB.txt
	@echo ">>>>>>Running p2_e3"
	./p2_e3 radio_dfs.txt 1 9

runv:
	@echo ">>>>>>Running p2_e1 with valgrind"
	valgrind --leak-check=full ./p2_e1 radio.txt
	@echo ">>>>>>Running p2_e2a with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e2a playlist1.txt playlist2.txt
	@echo ">>>>>>Running p2_e2b with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p2_e2b playlistA.txt playlistB.txt
	@echo ">>>>>>Running p2_e3 with valgrind"
	valgrind --leak-check=full ./p2_e3 radio_dfs.txt 1 9
