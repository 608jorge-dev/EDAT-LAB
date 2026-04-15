########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -std=c90
LIBS = -lstack -L.
EJS = p3_e1 p3_e2 p3_e3 p3_e1s p3_e2s test_queue test_list test_queues
########################################################
OBJECTSP3E1 = p3_e1.o radio.o music.o queue.o
OBJECTSP3E2 = p3_e2.o radio.o music.o queue.o
OBJECTSP3E3 = p3_e3.o radio.o music.o list.o
OBJECTSP3E1S = p3_e1.o radio.o music.o queuelist.o list.o
OBJECTSP3E2S = p3_e2.o radio.o music.o queuelist.o list.o
########################################################

all: $(EJS)

.PHONY: all clean clear run run_test runv queue_test test_list

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1) $(LIBS)

p3_e2: $(OBJECTSP3E2)
	$(CC) $(CFLAGS) -o p3_e2 $(OBJECTSP3E2) $(LIBS)

p3_e3: $(OBJECTSP3E3)
	$(CC) $(CFLAGS) -o p3_e3 $(OBJECTSP3E3) $(LIBS)

p3_e1s: $(OBJECTSP3E1S)
	$(CC) $(CFLAGS) -o p3_e1s $(OBJECTSP3E1S) $(LIBS)

p3_e2s: $(OBJECTSP3E2S)
	$(CC) $(CFLAGS) -o p3_e2s $(OBJECTSP3E2S) $(LIBS)

test_queue: test_queue.o queue.o
	$(CC) $(CFLAGS) -o test_queue test_queue.o queue.o $(LIBS)

test_queues: test_queue.o queuelist.o 
	$(CC) $(CFLAGS) -o test_queues test_queue.o queuelist.o list.o $(LIBS)

test_list: test_list.o list.o
	$(CC) $(CFLAGS) -o test_list test_list.o list.o $(LIBS)

########################################################

p3_e1.o: p3_e1.c music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2.o: p3_e2.c music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p3_e2.c
	
p3_e3.o: p3_e3.c music.h radio.h list.h
	$(CC) $(CFLAGS) -c p3_e3.c

p3_e1s.o: p3_e1.c music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p3_e1.c

p3_e2s.o: p3_e2.c music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p3_e2.c

music.o: music.c music.h 
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

queue.o: queue.c queue.h music.h
	$(CC) $(CFLAGS) -c queue.c

test_queue.o: test_queue.c queue.h
	$(CC) -c test_queue.c

test_list.o: test_list.c list.h
	$(CC) -c test_list.c

list.o: list.c list.h music.h
	$(CC) $(CFLAGS) -c list.c

queuelist.o: queuelist.c
	$(CC) $(CFLAGS) -c queuelist.c

########################################################

clear:
	rm -rf *.o $(EJS) 

run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 radio.txt
	@echo ">>>>>>Running p3_e2"
	./p3_e2 radio_bfs.txt 1 2
	@echo ">>>>>>Running p3_e3"
	./p3_e3 radio_bfs.txt
	@echo ">>>>>>Running p3_e1s"
	./p3_e1s radio.txt
	@echo ">>>>>>Running p3_e2s"
	./p3_e2s radio_bfs.txt 1 2

run_test:
	@echo ">>>>>>Running test_queue"
	valgrind --leak-check=full ./test_queue
	@echo ">>>>>>Running test_list"
	valgrind --leak-check=full ./test_list
	@echo ">>>>>>Running test_queues"
	valgrind --leak-check=full ./test_queues
	
runv:
	
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full ./p3_e1 radio.txt
	@echo ">>>>>>Running p3_e2 with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e2 radio_bfs.txt 1 2
	@echo ">>>>>>Running p3_e3 with valgrind"
	valgrind --leak-check=full ./p3_e3 radio_bfs.txt
	@echo ">>>>>>Running p3_e1s with valgrind"
	valgrind --leak-check=full ./p3_e1s radio.txt
	@echo ">>>>>>Running p3_e2s with valgrind"
	valgrind --leak-check=full --track-origins=yes ./p3_e2s radio_bfs.txt 1 2
