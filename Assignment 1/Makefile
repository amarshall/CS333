##
# Makefile
# CS333 Assignment #1
# @author J. Andrew Marshall (jmarsha6)
#

all: risort llmergesort

risort: insertion.o
	g++ -g insertion.o -o risort

insertion.o: insertion.cpp
	g++ -g -c insertion.cpp

llmergesort: merge.o Node.o
	g++ -g merge.o Node.o -o llmergesort

merge.o: merge.cpp
	g++ -g -c merge.cpp

Node.o: Node.cpp
	g++ -g -c Node.cpp

clean:
	rm -f *.o risort llmergesort ~*
