CC = g++
CFLAGS  = -g -Wall -lstdc++

all: escalona

escalona:  escalona.o grafo.o  
	$(CC) $(CFLAGS) -o escalona escalona.o grafo.o 

escalona.o:  escalona.cpp  grafo.h
	$(CC) $(CFLAGS) -c escalona.cpp

grafo.o:  grafo.cpp grafo.h
	$(CC) $(CFLAGS) -c grafo.cpp

clean: 
	$(RM) count *.o *~