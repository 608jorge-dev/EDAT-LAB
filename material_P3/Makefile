########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -std=c90
EJS = p3_e1 
########################################################
OBJECTSP3E1 = p3_e1.o radio.o music.o queue.o
# OBJECTSP3E2 = p3_e2.o radio.o music.o
# OBJECTSP3E3 = p3_e3.o radio.o music.o
########################################################

all: $(EJS) clear

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

# p3_e2: $(OBJECTSP3E2)
# 	$(CC) $(CFLAGS) -o p3_e2 $(OBJECTSP3E2)

# p3_e3: $(OBJECTSP3E3)
# 	$(CC) $(CFLAGS) -o p3_e3 $(OBJECTSP3E3)


p3_e1.o: p3_e1.c music.h radio.h stack.h
	$(CC) $(CFLAGS) -c p3_e1.c

# p3_e2.o: p3_e2.c music.h radio.h
# 	$(CC) $(CFLAGS) -c p3_e2.c
	
# p3_e3.o: p3_e3.c music.h radio.h
# 	$(CC) $(CFLAGS) -c p3_e3.c

music.o: music.c music.h 
	$(CC) $(CFLAGS) -c music.c

radio.o: radio.c radio.h music.h
	$(CC) $(CFLAGS) -c radio.c

queue.o: queue.c queue.h music.h
	$(CC) $(CFLAGS) -c queue.c


clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 radio.txt
# 	@echo ">>>>>>Running p3_e2"
# 	./p3_e2 
# 	@echo ">>>>>>Running p3_e3"
# 	./p3_e3 

runv:
	
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full ./p3_e1 radio.txt
# 	@echo ">>>>>>Running p3_e2 with valgrind"
# 	valgrind --leak-check=full --track-origins=yes ./p3_e2 
# 	@echo ">>>>>>Running p3_e3 with valgrind"
# 	valgrind --leak-check=full ./p3_e3
