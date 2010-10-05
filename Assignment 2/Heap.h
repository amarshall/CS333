class Heap {
	protected:
		int size;
		int heapSize;
		int* heap;
		const int* emails;
		void heapify(int i);
		virtual bool compare(const void* first, const void* second, const Email* emails) const;
	public:
		Heap(int* arr, int s);
		void heapSort();
		void printHeap();
		void buildHeap();
		int* getHeap();
};

class DateHeap : public Heap {
	private:
		bool compare(const int* first, const int* second, const Email* emails) const {
			return emails[*first].timestamp > emails[*second].timestamp;
		}
	public:
		DateHeap(int* arr, int s) : Heap(arr, s) {};
};
