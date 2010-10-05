class Heap {
	protected:
		int size;
		int heapSize;
		int* heap;
		const Email* emails;
		void heapify(int i);
		virtual bool compare(const void* first, const void* second) const;
		friend std::ostream& operator<<(std::ostream& output, const Heap& h);
	public:
		Heap(int* arr, int s, const Email* e);
		void heapSort();
		void printHeap();
		void buildHeap();
		int* getHeap();
};

class DateHeap : public Heap {
	private:
		bool compare(const int* first, const int* second) const {
			return emails[*first].timestamp > emails[*second].timestamp;
		}
	public:
		DateHeap(int* arr, int s, const Email* e) : Heap(arr, s, e) {};
};

class SubjectHeap : public Heap {
	private:
		bool compare(const int* first, const int* second) const {
			return emails[*first].subject.compare(emails[*second].subject);
		}
	public:
		SubjectHeap(int* arr, int s, const Email* e) : Heap(arr, s, e) {};
};

class LinesHeap : public Heap {
	private:
		bool compare(const int* first, const int* second) const {
			return emails[*first].lineCount < emails[*second].lineCount;
		}
	public:
		LinesHeap(int* arr, int s, const Email* e) : Heap(arr, s, e) {};
};
