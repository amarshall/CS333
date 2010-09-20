/**
 * Node.h
 * CS333 Assignment #1
 * @author J. Andrew Marshall (jmarsha6)
 */

#ifndef NODE_H__
#define NODE_H__

#include <string>

class Node {
 	public:
		int data;
		Node* next;
      Node* prev;
	
	public:
		Node();
		Node(int dataIn, Node* nextIn, Node* prevIn);
		Node *getNext();
      Node *getPrev();
		void setNext(Node* nextIn);
		void setPrev(Node* prevIn);
		int getData();
		void setData(int dataIn);
		~Node();
};

#endif // NODE_H__

