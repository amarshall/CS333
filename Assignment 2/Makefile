##
# Makefile
# CS333 Assignment #2
# @author J. Andrew Marshall (jmarsha6)
#

GXX=g++ -Wall -g

all: multi_heap

multi_heap: main.o Heap.o Email.o
	$(GXX) main.o Heap.o Email.o -o multi_heap

Heap.o: Heap.cpp Heap.h
	$(GXX) -c Heap.cpp

Email.o: Email.cpp Email.h
	$(GXX) -c Email.cpp

main.o: main.cpp
	$(GXX) -c main.cpp


clean:
	rm -f *.o ~* core multi_heap
