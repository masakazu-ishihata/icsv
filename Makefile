# Makefile
TAR = test
CC = gcc -O6 -Wall
L = -lm -lilist -listring
OBJS = main.o icsv.o
SHAD = -fPIC -shared
LIB = libicsv.so

all : $(TAR) lib
$(TAR): $(OBJS)
	  $(CC) -o $@ $(OBJS) $(L)
clean:
	  rm -f $(OBJS) $(TAR) $(LIB) *~ *.bak

.c.o:	  $(CC) -c $<

lib:
	$(CC) $(SHAD) -o $(LIB) icsv.c $(L)

main.o: main.h icsv.o
icsv.o: icsv.h
