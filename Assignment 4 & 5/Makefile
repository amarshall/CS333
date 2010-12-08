##
# Makefile
# CS333 Assignment #4 & 5
# @author J. Andrew Marshall (jmarsha6)
#

GXX=g++ -Wall

all: huffman

huffman: main.o
	$(GXX) main.o -o huffman

main.o: main.cpp
	$(GXX) -c main.cpp


clean:
	rm -f *.o ~* core huffman
