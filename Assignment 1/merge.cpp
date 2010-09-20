/**
 * merge.cpp
 * CS333 Assignment #1
 * @author J. Andrew Marshall (jmarsha6)
 *
 * WARNING: This code contains some mild black magic.
 */

#include <iostream>
#include "Node.h"

using namespace std;

void printList(Node* node) {
	while(node->getPrev() != NULL) {
		node = node->getPrev();
	}
	while(node != NULL) {
		cout << node->getData() << endl;
		node = node->getNext();
	}
}

int getListLength(Node* start, Node* end) {
	int length = 1;
	Node* cur = start;
	while(cur != end) {
		cur = cur->next;
		length++;
	}
	return length;
}

Node* merge(Node* start, Node* end, Node* pivot, int length) {
	Node* cur1 = start;
	Node* cur2 = pivot->getNext();
	Node* stop = end->getNext();
	while(cur1 != pivot->getNext() && cur2 != stop) {
		if(cur1->getData() > cur2->getData()) {
			Node* tmp = cur2;
			cur2->getPrev()->setNext(cur2->getNext());
			if(cur2->getNext() != NULL) {
				cur2->getNext()->setPrev(cur2->getPrev());
			}
			cur2 = cur2->getNext();  // Look at next in right on next loop
			if(cur1->getPrev() != NULL) {
				cur1->getPrev()->setNext(tmp);
			}
			tmp->setPrev(cur1->getPrev());
			cur1->setPrev(tmp);
			tmp->setNext(cur1);
			if(cur1 == start) {
				start = tmp;
			}
		} else {
			cur1 = cur1->getNext();  // Look at next in left on next loop
		}
	}
	return start;  // Because it's very possible this is different now
}

Node* mergeSort(Node* start, Node* end) {
	Node* ret = NULL;
	int length = getListLength(start, end);
	if(length >= 2) {
		Node* pivot = start;
		for(int i=0; i < length/2 - 1; ++i) {
			pivot = pivot->getNext();
		}
		
		// Need to save since their predecessors will probably change
		Node* pivot_next = pivot->getNext();
		Node* end_next = end->getNext();
		
		// Entering left
		Node* s = mergeSort(start, pivot);
		start = (s != NULL) ? s : start;
		
		// Entering right
		Node* p = (mergeSort(pivot_next, end));
		pivot = (p != NULL) ? p->getPrev() : pivot;
		
		// Merging
		// Need to make sure we have the true end of the list
		if(end_next == NULL) {
			end_next = end;
			while(end_next->getNext() != NULL) {
				end_next = end_next->getNext();
			}
		} else {
			end_next = end_next->getPrev();
		}
		ret = merge(start, end_next, pivot, length);
	}
	return ret;
}

int main() {
	int val;
	Node* values = NULL;
	Node* cur;
	while(cin >> val) {
		if(values == NULL) {
			values = new Node(val, NULL, NULL);  // Hopefully 1st alloc doesn't fail
			cur = values;
		} else {
			try {
				cur->next = new Node(val, NULL, cur);
			} catch (bad_alloc& e) {  // I think I did this right...
				cerr << "KABOOM! Ran out of memory; exiting." << endl;
				cerr << e.what() << endl;
				exit(1);
			}
			cur = cur->next;
		}
	}
	/*
	int arr[] = { 41, 26, 57, 98, 69, 93, 56, 61, 71, 95, 24, 72, 67, 51, 86, 75, 22, 87, 85, 77, 44, 13, 52, 28, 73 };
	for(int i=0; i<25; ++i) {
		val = arr[i];
		if(values == NULL) {
			values = new Node(val, NULL, NULL);
			cur = values;
		} else {
			cur->next = new Node(val, NULL, cur);
			cur = cur->next;
		}
	}
	*/
	mergeSort(values, cur);
	
	printList(values);
	
	return 0;
}