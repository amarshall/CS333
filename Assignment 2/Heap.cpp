#include "MaxHeap.h"

using namespace std;

Heap::Heap(int* arr, int s) {
  size = s;
  heap = new int[s];
  for(int i=0; i<s; ++i) {
    heap[i] = arr[i];
  }
}

void Heap::heapify() {
  
}
