.PHONY: librn
.PHONY: clean

CC = gcc
LDFLAGS = -L. -lrn
CFLAGS = -Wall -Wextra

all: shipbattle librn

shipbattle: shipbattle.c gameplay.o gameboard.o librn 
	$(CC) $(CFLAGS) shipbattle.c gameplay.o gameboard.o $(LDFLAGS)

gameplay.o: gameplay.c gameboard.h gameplay.h 
	$(CC) $(CFLAGS) -c gameplay.c 

gameboard.o: gameboard.c gameboard.h rand_num.h librn
	$(CC) $(CFLAGS) -c gameboard.c $(LDFLAGS) 

rand_num.o: rand_num.c rand_num.h
	$(CC) $(CFLAGS) -c rand_num.c

librn.a: rand_num.o
	ar -r -c -s librn.a rand_num.o

rand_num_shared.o:  rand_num.c rand_num.h
	$(CC) $(CFLAGS) -fpic -c rand_num.c

librn.so: rand_num_shared.o
	$(CC) $(CFLAGS) -shared -o librn.so rand_num.o

librn: librn.a librn.so

clean:
	rm -f *.o *.a *.so *.out

