CC=gcc
CFLAGS=-Wall -Werror -fopenmp
FICHIERO= GaussJordan.o main.o

default: clean GaussJordan main compile 
	rm -f *.o
		
compile: 
	$(CC) $(CFLAGS) $(FICHIERO) -o 
	
%: %.c
	$(CC) $(CFLAGS) $@.c -o $@.o

clean:
	clear
	rm -f *.o
	rm -f exemple
