class Heap {
   private:
      int size;
      int heapSize;
      int* heap;
      void buildHeap();
      void heapify(int i);
   public:
      Heap(int* arr, int s);
      void heapSort();
};
