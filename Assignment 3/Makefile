##
# Makefile
# CS333 Assignment #3
# @author J. Andrew Marshall (jmarsha6)
#

GXX=g++ -Wall

all: ssort ssort_contest

ssort_contest: ssort
	cp ssort ssort_contest

ssort: main.o
	$(GXX) main.o -o ssort

main.o: main.cpp
	$(GXX) -c main.cpp


clean:
	rm -f *.o ~* core ssort
