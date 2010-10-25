##
# Makefile
# CS333 Assignment #3
# @author J. Andrew Marshall (jmarsha6)
#

GXX=g++ -Wall -pthread

all: ssort

ssort: main.o
	$(GXX) main.o -o ssort

main.o: main.cpp
	$(GXX) -c main.cpp


clean:
	rm -f *.o ~* core ssort
