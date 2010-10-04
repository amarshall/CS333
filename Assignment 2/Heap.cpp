#include "Heap.h"
#include <iostream>

using namespace std;

Heap::Heap(int* arr, int s) {
  size = s;
  heap = new int[s];
  for(int i=0; i<s; ++i) {
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
  largest = (left <= heapSize-1 && heap[left] > heap[i]) ? left : i;
  if(right <= heapSize-1 && heap[right] > heap[largest]) {
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
