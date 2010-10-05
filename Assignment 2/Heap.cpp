#include <iostream>
#include "Email.h"
#include "Heap.h"

using namespace std;

Heap::Heap(int* arr, int s, const Email* e) {
	size = s;
	emails = e;
	heap = new int[size];
	for(int i=0; i<size; ++i) { heap[i] = arr[i]; }
}

void Heap::heapSort() {
	buildHeap();
	for(int i=size-1; i>=1; --i) {
		int tmp = heap[0];
		heap[0] = heap[i];
		heap[i] = tmp;
		--heapSize;
		heapify(0);
	}
}

void Heap::buildHeap() {
	heapSize = size;
	for(int i=(size-1)/2; i>=0; --i) {
		heapify(i);
	}
}

void Heap::buildHeap(int* arr) {
	--size;
	for(int i=0; i<size; ++i) { heap[i] = arr[i]; }
	buildHeap();
}

void Heap::heapify(int i) {
	int largest;
	int left = 2*i + 1;
	int right = 2*i + 2;
	
	largest = (left <= heapSize-1 && compare(left, i)) ? left : i;
	if(right <= heapSize-1 && compare(right, largest)) {
		largest = right;
	}
	if(largest != i) {
		int tmp = heap[i];
		heap[i] = heap[largest];
		heap[largest] = tmp;
		heapify(largest);
	}
}

int* Heap::popTop() {
	int tmp = heap[0];
	heap[0] = heap[size-1];
	heap[size-1] = tmp;
	--size;
	heapSize = size;
	heapify(0);
	return heap;
}

int* Heap::getHeap() {
	return heap;
}

ostream& operator<<(ostream& output, const Heap& h) {
	for(int i=h.size-1; i>=0; --i) {
		output << h.emails[h.heap[i]];
	}
	return output;
}

/* Please overload me. Defaults to max heap. */
bool Heap::compare(int first, int second) const {
	return first > second;
}


DateHeap::DateHeap(int* arr, int s, const Email* e) : Heap(arr, s, e) {}

bool DateHeap::compare(int first, int second) const {
	return emails[heap[first]].timestamp < emails[heap[second]].timestamp;
}


SubjectHeap::SubjectHeap(int* arr, int s, const Email* e) : Heap(arr, s, e) {}

bool SubjectHeap::compare(int first, int second) const {
	return emails[heap[first]].subject.compare(emails[heap[second]].subject) < 0;
}


LinesHeap::LinesHeap(int* arr, int s, const Email* e) : Heap(arr, s, e) {}

bool LinesHeap::compare(int first, int second) const {
	return emails[heap[first]].lineCount > emails[heap[second]].lineCount;
}
