class MaxHeap {
   private:
      int size;
      int* heap;
   public:
      MaxHeap(int* arr, int s);
      void heapify();
};
