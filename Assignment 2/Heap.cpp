#include <iostream>
#include "Email.h"
#include "Heap.h"

using namespace std;

Heap::Heap(int* arr, int s, const Email* e) {
	size = s;
	emails = e;
	heap = new int[size];
	for(int i=0; i<size; ++i) {
		heap[i] = arr[i];
	}
}

void Heap::heapSort() {
	buildHeap();
	for(int i=size-1; i>=1; --i) {
		int tmp = heap[0];
		heap[0] = heap[i];
		heap[i] = tmp;
		--heapSize;
		heapify(1);
	}
}

void Heap::buildHeap() {
	heapSize = size;
	for(int i=(size-1)/2; i>=0; --i) {
		heapify(i);
	}
}

void Heap::heapify(int i) {
	int largest;
	int left = 2*i + 1;
	int right = 2*i + 2;
	largest = (left <= heapSize-1 && this->compare(&left, &i)) ? left : i;
	if(right <= heapSize-1 && compare(&right, &largest)) {
		largest = right;
	}
	if(largest != i) {
		int tmp = heap[i];
		heap[i] = heap[largest];
		heap[largest] = tmp;
		heapify(largest);
	}
}

int* Heap::getHeap() {
	return heap;
}

void Heap::printHeap() {
	for(int i=0; i<size; ++i) {
		cout << heap[i] << endl;
	}
}

ostream& operator<<(ostream& output, const Heap& h) {
	for(int i=0; i<h.size; ++i) {
		output << h.emails[h.heap[i]];
	}
	return output;
}

/* Please overload me */
bool Heap::compare(const void* first, const void* second) const {
	return true;
}
