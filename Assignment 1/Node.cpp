/**
 * Node.cpp
 * CS333 Assignment #1
 * @author J. Andrew Marshall (jmarsha6)
 */

#include "Node.h"

using namespace std;

/* Empty constructor, initializes private data to NULL */
Node::Node() {
	next = NULL;
	prev = NULL;
}

/**
 * Explicit value constructor
 *
 * @param *dataIn The StudentRecord the new Node will contain
 * @param *nextIn Pointer to the Node after the new Node
 */
Node::Node(int dataIn, Node* nextIn, Node* prevIn) {
	data = dataIn;
	next = nextIn;
	prev = prevIn;
}

/* @returns Pointer to the node after this */
Node* Node::getNext() {
	return next;
}

/* @param *nextIn Node that follows this one */
void Node::setNext(Node* nextIn) {
	next = nextIn;
}

Node* Node::getPrev() {
	return prev;
}

/* @param *nextIn Node that follows this one */
void Node::setPrev(Node* prevIn) {
	prev = prevIn;
}

/* @returns the StudentRecord this Node contains */
int Node::getData() {
	return data;
}

/* @param *dataIn The StudentRecord that the Node should now contain */
void Node::setData(int dataIn) {
	data = dataIn;
}

/* Destructor, deletes the StudentRecord contained within the Node */
Node::~Node() {
	// Next pointer is deleted by LinkedList.cpp
}
