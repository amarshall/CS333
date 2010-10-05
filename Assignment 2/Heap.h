class Heap {
	protected:
		int size;
		int heapSize;
		int* heap;
		const Email* emails;
		void heapify(int i);
		virtual bool compare(int first, int second) const;
		friend std::ostream& operator<<(std::ostream& output, const Heap& h);
	public:
		Heap(int* arr, int s, const Email* e);
		void heapSort();
		void printHeap();
		void buildHeap();
		void buildHeap(int* arr);
		int* popTop();
		int* getHeap();
};

class DateHeap : public Heap {
	protected:
		bool compare(int first, int second) const;
	public:
		DateHeap(int* arr, int s, const Email* e);
};

class SubjectHeap : public Heap {
	protected:
		bool compare(int first, int second) const;
	public:
		SubjectHeap(int* arr, int s, const Email* e);
};

class LinesHeap : public Heap {
	protected:
		bool compare(int first, int second) const;
	public:
		LinesHeap(int* arr, int s, const Email* e);
};
