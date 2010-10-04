class Heap {
   private:
      int size;
      int heapSize;
      int* heap;
      void heapify(int i);
   public:
      Heap(int* arr, int s);
      void heapSort();
      void printHeap();
      void buildHeap();
      int* getHeap();
};
