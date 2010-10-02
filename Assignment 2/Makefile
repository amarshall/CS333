##
# Makefile
# CS333 Assignment #2
# @author J. Andrew Marshall (jmarsha6)
#

GXX=g++ -Wall -g

all: multi_heap

multi_heap: main.o MaxHeap.o Email.o
	$(GXX) main.o MaxHeap.o Email.o -o multi_heap

MaxHeap.o: MaxHeap.cpp MaxHeap.h
	$(GXX) -c MaxHeap.cpp

Email.o: Email.cpp Email.h
	$(GXX) -c Email.cpp


clean:
	rm -f *.o ~* core multi_heap
